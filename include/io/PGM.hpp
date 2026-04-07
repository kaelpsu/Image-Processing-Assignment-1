#pragma once
#include "core/Image.hpp"
#include <string>

using namespace std;

static void skipComments(ifstream& file);
Image readPGM(const std::string& filename);
void writePGM(const std::string& filename, const Image& img);