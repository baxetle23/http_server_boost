
#include "connection.hpp"
#include <utility>
#include <vector>
#include "connectionManager.hpp"
#include "requestHandler.hpp"

namespace http {
namespace server {

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
              do_write_body();
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

void connection::do_write_body() {
  auto self(shared_from_this());
  boost::asio::async_write(socket_, boost::asio::const_buffer(GIGA_BUFER.data(), GIGA_BUFER.size()),
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
        GIGA_BUFER.resize(0);
      });
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