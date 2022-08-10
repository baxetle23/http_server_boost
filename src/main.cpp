#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include "server.hpp"

using namespace std::literals;

int main(int argc, char **argv) {
    try {
        if (argc != 4) {
            std::cerr << "Usage: http_server <addres> <port> <doc_root>"s << std::endl;
            std::cerr << " For IPv4, try:"s << std::endl;
            std::cerr << "  receiver 0.0.0.0 80 ."s << std::endl;
            std::cerr << " For IPv6, try:"s << std::endl;
            std::cerr << "  receiver 0::0 80 ."s << std::endl;
            return 1;
        }

        http::server::server s(argv[1], argv[2], argv[3]);
        s.run();
    } catch(std::exception& exc) {
        std::cerr << "exception: "s << exc.what() << std::endl;
    }
}