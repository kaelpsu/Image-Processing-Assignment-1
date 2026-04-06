#pragma once
#include <vector>
#include <string>

class Image {
public:
    int width;
    int height;
    int maxVal;

    std::vector<std::vector<int>> pixels;

    Image(int w, int h, int maxVal);

    static Image readPGM(const std::string& filename);
    
    void writePGM(const std::string& filename) const;
};