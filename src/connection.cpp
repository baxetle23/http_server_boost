
#include "connection.hpp"
#include <utility>
#include <vector>
#include "connectionManager.hpp"
#include "requestHandler.hpp"


#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.hpp"
#include "stb_image_write.hpp"

namespace http {
namespace server {

typedef struct {
    int last_pos;
    void *context;
} custom_stbi_mem_context;

// custom write function
static void custom_stbi_write_mem(void *context, void *data, int size) {
   custom_stbi_mem_context *c = (custom_stbi_mem_context*)context; 
   char *dst = (char *)c->context;
   char *src = (char *)data;
   int cur_pos = c->last_pos;
   for (int i = 0; i < size; i++) {
       dst[cur_pos++] = src[i];
   }
   c->last_pos = cur_pos;
}

connection::connection(boost::asio::ip::tcp::socket socket,
                        connection_manager& manager, request_handler& handler) :
    socket_(std::move(socket)),
    connection_manager_(manager),
    request_handler_(handler) {
}

void connection::start() {
  do_read();
}

void connection::stop() {
  socket_.close();
}

std::vector<char> rBuffer(102400);
std::vector<char> GIGA_BUFER;

boost::asio::streambuf b;

void connection::do_read_body() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(rBuffer.data(), rBuffer.size()),
                            [&](boost::system::error_code ec, size_t length) {
        if (!ec) {
            std::cout << "\n\nRead " << length << " bytes" << std::endl;
            for(int i = 0; i < length; ++i) {
                GIGA_BUFER.push_back(rBuffer[i]);
            }
            if (GIGA_BUFER.size() == 1659050) {
              std::cout << "THIS IS WE MAST SEE END" << std::endl;
              
              int width, height, channels;
              unsigned char* img = stbi_load_from_memory(
                  (const unsigned char*)GIGA_BUFER.data(), GIGA_BUFER.size(), &width, &height, &channels, 0);
              unsigned char buffer[width * channels];
              for(size_t i = 0; i < height / 2; ++i) {
                memcpy(buffer, img + width * channels * i, width * channels);
                memcpy(img + width * channels * i, img + (height - i - 1) * width * channels, width * channels);
                memcpy(img + (height - i - 1) * width * channels, buffer, width * channels);
              }

              custom_stbi_mem_context context;
              context.last_pos = 0;
              context.context = (void *)GIGA_BUFER.data();
              int result = stbi_write_jpg_to_func(custom_stbi_write_mem, &context, width, height, channels, img, 20);
              std::cout << context.last_pos << std::endl;
              // stbi_write_jpg("cat-copy_fromserver.jpg", width, height, channels, img, 100);


              reply_.status = reply::ok;
              reply_.content.append(GIGA_BUFER.data(), GIGA_BUFER.size());
              reply_.headers.resize(2);
              reply_.headers[0].name = "Content-Length";
              reply_.headers[0].value = std::to_string(reply_.content.size());
              reply_.headers[1].name = "Content-Type";
              reply_.headers[1].value = "image/jpeg";
              GIGA_BUFER.resize(0);

              do_write();
            } else {
              do_read_body();
            }

        }
    });
}


void connection::do_read() {
    auto self(shared_from_this());
    boost::asio::async_read_until(socket_, b, "\r\n\r\n",
      [&](boost::system::error_code ec, size_t bytes_transferred){
        std::istream is(&b);
        std::vector<char> buffer_header(bytes_transferred);
        std::string line;
        while(std::getline(is, line)) {
          std::cout << line << std::endl;
        }
        do_read_body();

      });
      
    // auto self(shared_from_this());
    // socket_.async_read_some(boost::asio::buffer(buffer_),
    //     [this, self](boost::system::error_code ec, std::size_t bytes_transferred) {
    //         if (!ec) {

    //             request_parser::result_type result;
    //             std::tie(result, std::ignore) = request_parser_.parse(
    //                 request_, buffer_.data(), buffer_.data() + bytes_transferred);

    //             if (result == request_parser::good) {
    //                 request_handler_.handle_request(request_, reply_);
    //                 do_write();
    //             } else if (result == request_parser::bad) {
    //                 reply_ = reply::stock_reply(reply::bad_request);
    //                 do_write();
    //             } else {
    //                 do_read();
    //             }
    //         } else if (ec != boost::asio::error::operation_aborted) {
    //             connection_manager_.stop(shared_from_this());
    //         }
    //     });
}

void connection::do_write() {
  auto self(shared_from_this());
  boost::asio::async_write(socket_, reply_.to_buffers(),
      [this, self](boost::system::error_code ec, std::size_t)
      {
        if (!ec)
        {
          // Initiate graceful connection closure.
          boost::system::error_code ignored_ec;
          socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
            ignored_ec);
        }

        if (ec != boost::asio::error::operation_aborted)
        {
          connection_manager_.stop(shared_from_this());
        }
      });
}

} // namespace server
} // namespace http