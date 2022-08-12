

#include "requestHandler.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "reply.hpp"
#include "request.hpp"

namespace http {
namespace server {

request_handler::request_handler() {
}

void request_handler::handle_request(const request& req, reply& rep) {
}

} // namespace server
} // namespace http