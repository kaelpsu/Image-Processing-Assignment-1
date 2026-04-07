#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "io/PNG.hpp"
#include "external/stb_image.h"
#include "external/stb_image_write.h"
#include <iostream>
#include <algorithm>

using namespace std;

Image readPNG(const std::string& filename) {
    int width, height, channels;

    unsigned char* data = stbi_load(
        filename.c_str(),
        &width,
        &height,
        &channels,
        1 // força grayscale
    );

    if (!data) {
        cerr << "Erro ao carregar PNG\n";
        exit(1);
    }

    Image img(width, height, 255);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            img.pixels[i][j] = data[i * width + j];
        }
    }

    stbi_image_free(data);
    return img;
}

void writePNG(const std::string& filename, const Image& img) {
    int width = img.width;
    int height = img.height;

    unsigned char* data = new unsigned char[width * height];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int pixelValue = img.pixels[i][j];
            int clampedValue = std::clamp(pixelValue, 0, 255);
            data[i * width + j] = static_cast<unsigned char>(clampedValue);
        }
    }

    stbi_write_png(
        filename.c_str(),
        width,
        height,
        1, // grayscale
        data,
        width
    );

    delete[] data;
}