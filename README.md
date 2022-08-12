# http_server_boost

HTTP service that accepts requests for horizontal image mirroring.

The client sends a JPEG-encoded image in the request body and 
receives a response from the service in the form of another JPEG image
For example , from ≒ it turns out ≓

Example of checking a service running on port 5875 use the curl utility:
>> curl -s --data-binary @image.jpg 127.0.0.1:5875 -o out.jpg

# start ttp_server_boost

>> 