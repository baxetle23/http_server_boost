# http_server_boost

HTTP service that accepts requests for horizontal image mirroring.

The client sends a JPEG-encoded image in the request body and 
receives a response from the service in the form of another JPEG image
For example , from ≒ it turns out ≓

an example was taken as the basis of the HTTP Server -> 
https://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/examples/cpp11_examples.html

# start http_server_boost

Clone the repository to your computer
> git clone https://github.com/baxetle23/http_server_boost.git http_server/

Create the build folder and go into it, there we will build the project
> cd http_server/ && mkdir build && cd build

run the project build script using make and make
> cmake .. && make

start server, the first argument is the ip address, the second port
> ./http_server 127.0.0.1 5865

Example of checking a service running on port 5865 use the curl utility from root project:
> curl -s --data-binary @cat.jpg 127.0.0.1:5865 -o out.jpg