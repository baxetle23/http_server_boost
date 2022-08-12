
#include "connection.hpp"
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

void connection::do_read_body() {
    auto self(shared_from_this());
    async_read(socket_, boost::asio::buffer(image_.imgBuffer.data(), image_.size_image),
                            [&](boost::system::error_code ec, size_t) {
        if (!ec) {
              ///work with image
              image_.flipImage();
              //creat responce
              reply_.status = reply::ok;
              reply_.content.append(image_.imgBuffer.data(), image_.imgBuffer.size());
              reply_.headers.resize(2);
              reply_.headers[0].name = "Content-Length";
              reply_.headers[0].value = std::to_string(reply_.content.size());
              reply_.headers[1].name = "Content-Type";
              reply_.headers[1].value = "image/jpeg";
              image_.imgBuffer.resize(0);

              do_write();
        }
    });
}

void connection::do_read() {
  auto self(shared_from_this());
  boost::asio::async_read_until(socket_, streamBuffer, "\r\n\r\n",
    [&](boost::system::error_code ec, size_t bytes_transferred){
      if (!ec) {
        std::istream is(&streamBuffer);
        std::vector<char> buffer_header(bytes_transferred);
        std::string line;
        while(std::getline(is, line)) {
          if (!line.find("Content-Length: ")) {
            image_.size_image = atoi(line.data() + 16);
            image_.imgBuffer.resize(image_.size_image);
          }
        }
        do_read_body();
      } else {
        connection_manager_.stop(shared_from_this());
      }
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