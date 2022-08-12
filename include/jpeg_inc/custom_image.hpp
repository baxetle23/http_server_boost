#pragma once 

#include <vector>
#include <cstring>

namespace image {

struct custom_stbi_mem_context{
    int last_pos;
    void *context;
};

// custom write function for work image to memory
void custom_stbi_write_mem(void *context, void *data, int size);

struct myImage {
    int size_image; // maybe overflow :)
    std::vector<char> imgBuffer;
    void flipImage();
};

}//namespace image