#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include "server.hpp"
#include "parameters_input.hpp"

using namespace std::literals;

int main(int argc, char **argv) {
    try {
        if (argc != 3) {
            std::cerr << "Usage: http_server <addres> <port>"s << std::endl;
            std::cerr << " For IPv4, try:"s << std::endl;
            std::cerr << "  receiver 0.0.0.0 80 ."s << std::endl;
            std::cerr << " For IPv6, try:"s << std::endl;
            std::cerr << "  receiver 0::0 80 ."s << std::endl;
            return 1;
        }

        auto parameters = get_parameters(argc, argv);

        http::server::server s(argv[1], argv[2]);
        s.run();
    } catch(std::exception& exc) {
        std::cerr << "exception: "s << exc.what() << std::endl;
    }
}