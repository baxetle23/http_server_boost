#include "custom_image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.hpp"
#include "stb_image_write.hpp"
#include <cstring>

#include <iostream>

namespace image {

// custom write function for work image to memory
void custom_stbi_write_mem(void *context, void *data, int size) {
   custom_stbi_mem_context *c = (custom_stbi_mem_context*)context; 
   char *dst = (char *)c->context;
   char *src = (char *)data;
   int cur_pos = c->last_pos;
   for (int i = 0; i < size; i++) {
       dst[cur_pos++] = src[i];
   }
   c->last_pos = cur_pos;
}

void myImage::flipImage() {
    if (!imgBuffer.size()) {
        return;
    }
    int width, height, channels;
    unsigned char* img = stbi_load_from_memory(
        (const unsigned char*)imgBuffer.data(), imgBuffer.size(), &width, &height, &channels, 0);
    unsigned char buffer[width * channels];
    for(int i = 0; i < height / 2; ++i) {
        std::memcpy(buffer, img + width * channels * i, width * channels);
        std::memcpy(img + width * channels * i, img + (height - i - 1) * width * channels, width * channels);
        std::memcpy(img + (height - i - 1) * width * channels, buffer, width * channels);
    }

    image::custom_stbi_mem_context context;
    context.last_pos = 0;
    context.context = (void *)imgBuffer.data();
    int result = stbi_write_jpg_to_func(custom_stbi_write_mem, &context, width, height, channels, img, 80);
    //work image 
}

}//namespace image