cmake_minimum_required(VERSION 3.16)

project(http_server)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/boost_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/include/jpeg_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/include/server_inc
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/connection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/connectionManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mimeTypes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/reply.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/requestHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/requestParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/custom_image.cpp

)

add_executable(http_server ${SOURCES})

target_link_libraries(http_server pthread)
