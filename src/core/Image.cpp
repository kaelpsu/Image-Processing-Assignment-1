#include "core/Image.hpp"

using namespace std;

Image::Image(int w, int h, int maxVal)
    : width(w), height(h), maxVal(maxVal),
      pixels(h, vector<int>(w, 0)) {}