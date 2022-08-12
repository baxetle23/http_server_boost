#include <iostream>
#include <fstream>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"

using namespace std;

int main()
{
    int width, height, channels;
    // unsigned char* img = stbi_load("cat.jpg", &width, &height, &channels, 0);

    // if (img == 0) {
    //     cout << "Error loading image file" << endl;
    //     return -1;
    // }

    // cout << "Loading image\n";
    // cout << "\twidth = " << width << "\n";
    // cout << "\theight = " << height << "\n";
    // cout << "\tchannels = " << channels << "\n";


    // this is work copy all image
    // unsigned char *flip = (unsigned char *)malloc(width * height * channels);
    // for(size_t i = 0; i < height; ++i) {
    //     memcpy((flip + (height - i - 1) * width * channels), img + width * channels * i , width * channels);
    // }
    // stbi_write_jpg("cat-copy2.jpg", width, height, channels, flip, 100);    
    //--------------------



    // unsigned char buffer[width * channels];

    // //this is work - copy to buffer string
    // for(size_t i = 0; i < height / 2; ++i) {
    //     memcpy(buffer, img + width * channels * i, width * channels);
    //     memcpy(img + width * channels * i, img + (height - i - 1) * width * channels, width * channels);
    //     memcpy(img + (height - i - 1) * width * channels, buffer, width * channels);
    // }
    // //------------

    // stbi_write_jpg("cat-copy.jpg", width, height, channels, img, 100);    

    // stbi_image_free(img);




    std::ifstream input("/home/aponyatov/Desktop/http_server_jpeg/http_server_boost/jpg/cat.jpg", std::ios::binary | std::ios::in);
    char temp;
    std::vector<unsigned char> data;
    while (input.read(&temp, sizeof(char))) {
        data.push_back(temp);
    }

    std::cout << (int)data[0] << (int)data[1] << std::endl;

    unsigned char* img_from_vec = stbi_load_from_memory((const unsigned char*)data.data(), data.size(), &width, &height, &channels, 0);

    stbi_write_jpg("foto_from_data.jpg", width, height, channels, img_from_vec, 100);

    stbi_image_free(img_from_vec);

    return 0;
}