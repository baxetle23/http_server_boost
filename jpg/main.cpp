#include <iostream>
#include <fstream>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb/stb_image.h"
#include "stb/stb_image_resize.h"
#include "stb/stb_image_write.h"

using namespace std;

int main()
{
    int width, height, channels;
    unsigned char* img = stbi_load("cat.jpg", &width, &height, &channels, 0);


    if (img == 0) {
        cout << "Error loading image file" << endl;
        return -1;
    }

    cout << "Loading image\n";
    cout << "\twidth = " << width << "\n";
    cout << "\theight = " << height << "\n";
    cout << "\tchannels = " << channels << "\n";

    // for(size_t i = 0; i < height / 2; ++i) {
    //     memcpy(img + (height - i ) * width * 3, img + i * width * 3, width * 3);
    // }

    unsigned char *flip = (unsigned char *)malloc(width * height * channels);

    for(size_t i = 0; i < width * height * channels; ++i) {
        flip[width*height*channels - i - 1] = img[i];
    }

    stbi_write_jpg("cat-copy.jpg", width, height, channels, flip, 100);    

    stbi_image_free(img);
    return 0;
}