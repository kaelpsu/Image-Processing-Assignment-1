#pragma once
#include "core/Image.hpp"
#include <string>

Image readPNG(const std::string& filename);
void writePNG(const std::string& filename, const Image& img);