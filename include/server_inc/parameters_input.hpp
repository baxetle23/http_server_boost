#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <cstdint>
#include <string>

class parameters
{
public:
    parameters();

    bool debug() const;
    const std::string& port() const;
    const std::string& address() const;

    void set_debug(bool enabled);
    void set_address(const std::string& address);
    void set_port(const std::string& port);

private:
    bool debug_;
    std::string port_;
    std::string address_;
};

std::unique_ptr<parameters> get_parameters(int argc, char** argv);

