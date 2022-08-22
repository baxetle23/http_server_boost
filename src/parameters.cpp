#include "parameters_input.hpp"

#include <cstdlib>
#include <boost/asio/ip/address.hpp>
#include <boost/program_options.hpp>
#include <iostream>

namespace {

const std::string LOCALHOST_IP_ADDRESS_STRING("127.0.0.1");
const std::string DEFAULT_PORT("5865");

}

parameters::parameters()
    : debug_(false), port_(DEFAULT_PORT), address_(LOCALHOST_IP_ADDRESS_STRING) {
}

bool parameters::debug() const {
    return debug_;
}

const std::string& parameters::port() const {
    return port_;
}

const std::string& parameters::address() const {
    return address_;
}

void parameters::set_debug(bool value) {
    debug_ = value;
}

void parameters::set_port(const std::string& port) {
    port_ = port;
}

void parameters::set_address(const std::string& address) {
    address_ = address;
}

std::unique_ptr<parameters> get_parameters(int argc, char** argv) {
    std::unique_ptr<parameters> params(new parameters);

    namespace po = boost::program_options;
    po::options_description description("options");
    description.add_options()
            ("help", "Display this help message")
            ("debug,d", po::bool_switch()->default_value(false),
                    "Enable debug logging.")
            ("ip-address,a", po::value<std::string>()->default_value(LOCALHOST_IP_ADDRESS_STRING),
                    "The ip address running the server. ")
            ("port,p", po::value<std::string>()->default_value(DEFAULT_PORT),
                    "The port that the wamp router is listening for connections on.");

    po::variables_map variables;
    try {
        po::store(po::parse_command_line(argc, argv, description), variables);

        if (variables.count("help")) {
            std::cout << "Example Parameters" << std::endl
                    << description << std::endl;
            exit(0);
        }

        po::notify(variables);
    } catch(po::error& e) {
        std::cerr << "error: " << e.what() << std::endl << std::endl;
        std::cerr << description << std::endl;
        exit(-1);
    }

    params->set_debug(variables["debug"].as<bool>());
    params->set_port(variables["port"].as<std::string>());
    params->set_address(variables["ip-address"].as<std::string>());

    return params;
}
