cmake_minimum_required(VERSION 3.16)

project(http_server)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/boost
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -I ${CMAKE_CURRENT_SOURCE_DIR}/")


set(SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/connection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/connectionManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mimeTypes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/reply.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/requestHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/requestParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp
)

add_executable(http_server ${SOURCES})

target_link_libraries(http_server pthread)
