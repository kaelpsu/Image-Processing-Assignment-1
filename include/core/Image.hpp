#pragma once
#include <vector>

class Image {
public:
    int width;
    int height;
    int maxVal;

    std::vector<std::vector<int>> pixels;

    Image(int w, int h, int maxVal);
};