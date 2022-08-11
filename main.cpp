#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>


#include <iostream>

std::vector<char> vBuffer(20 * 1024);

void GetSomeData(boost::asio::ip::tcp::socket& socket) {
    socket.async_read_some(boost::asio::buffer(vBuffer.data(), vBuffer.size()),
                            [&](boost::system::error_code ec, size_t length) {
        if (!ec) {
            std::cout << "\n\nRead " << length << " bytes" << std::endl;
            for(int i = 0; i < length; ++i) {
                std::cout << vBuffer[i];

                GetSomeData(socket);
            }
        }
    });
}

using namespace boost;

int main() {
    boost::system::error_code ec;

    boost::asio::io_context context;

    boost::asio::io_context::work idleWork(context);

    std::thread thrContext = std::thread([&](){context.run();});

    boost::asio::tcp::end

    return 0;
}