#pragma once
#include "core/Image.hpp"
#include <string>

Image readImage(const std::string& filename);
void writeImage(const std::string& filename, const Image& img);