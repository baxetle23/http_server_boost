#pragma once

#include <boost/asio.hpp>
#include <array>
#include <memory>
#include <iostream>

#include "reply.hpp"
#include "request.hpp"
#include "requestHandler.hpp"
#include "requestParser.hpp"
#include "custom_image.hpp"

constexpr size_t SIZE_BUFFER_READ = 102400;

namespace http {
namespace server {

class connection_manager;

class connection : public std::enable_shared_from_this<connection> {
public:
    connection(const connection&) = delete;
    connection& operator=(const connection&) = delete;

    explicit connection(boost::asio::ip::tcp::socket socket,
                        connection_manager& manager,
                        request_handler& handler);
    
    void start();

    void stop();

private:
    void do_read();
    void do_read_body();

    void do_write();
    void do_write_body();

    boost::asio::ip::tcp::socket socket_;

    connection_manager& connection_manager_;

    request_handler& request_handler_;

    boost::asio::streambuf streamBuffer;

    request request_;

    request_parser request_parser_;

    image::myImage image_;

    reply reply_;
};

typedef std::shared_ptr<connection> connection_ptr;

}//namespace server
}//namespace http