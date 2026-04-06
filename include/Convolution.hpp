#pragma once
#include "Image.hpp"
#include <vector>

using Kernel = std::vector<std::vector<float>>;

Image convolve(
    const Image& img,
    const Kernel& kernel
);