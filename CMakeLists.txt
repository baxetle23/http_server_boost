cmake_minimum_required(VERSION 3.16)

project(http_server)

option(DEBUG_DATA_LOG "Build programm with data log" OFF)

if(DEBUG_DATA_LOG)
    add_compile_definitions(DEBUG_DATA_LOG)
endif(DEBUG_DATA_LOG)

message("CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/boost_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/include/jpeg_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/include/server_inc
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS}  -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS}  -O3")

set(SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/connection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/connectionManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/reply.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/requestHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/custom_image.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/basic_logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parameters.cpp
)

add_executable(http_server ${SOURCES})

target_link_libraries(http_server pthread)