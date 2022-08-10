#pragma once 

#include <set>
#include "connection.hpp"

namespace http {
namespace server {
class connection_manager {
public:
    connection_manager(const connection_manager&) = delete;
    connection_manager& operator=(const connection_manager&) = delete;

    connection_manager();

    void start(connection_ptr c_ptr);

    void stop(connection_ptr c_ptr);

    void stop_all();

private:

    std::set<connection_ptr> connections_;
};
}
} // namespace http