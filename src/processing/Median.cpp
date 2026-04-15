#include "processing/Median.hpp"

#include <algorithm>
#include <array>
#include <cstddef>

#include "core/Image.hpp"

template <int kernel_size>
Image median(const Image &input) {
    constexpr int offset = kernel_size / 2;
    constexpr int area = kernel_size * kernel_size;

    size_t width = input.width;
    size_t height = input.height;

    Image out(width, height, input.maxVal);

    std::array<int, area> neighbors;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            size_t idx = 0;
            for (int i_off = -offset; i_off <= offset; ++i_off) {
                for (int j_off = -offset; j_off <= offset; ++j_off) {
                    int clamped_i = std::clamp(i + i_off, 0, static_cast<int>(height) - 1);
                    int clamped_j = std::clamp(j + j_off, 0, static_cast<int>(width) - 1);
                    neighbors[idx++] = input.pixels[clamped_i][clamped_j];
                }
            }

            std::nth_element(neighbors.begin(), neighbors.begin() + area / 2, neighbors.end());
            out.pixels[i][j] = neighbors[area / 2];
        }
    }

    return out;
}

template Image median<3>(const Image &input);
template Image median<5>(const Image &input);
