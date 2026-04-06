#include "Convolution.hpp"
#include <algorithm>

using namespace std;

Image convolve(
    const Image& img,
    const Kernel& kernel
) {
    int rows = img.height;
    int cols = img.width;

    int d = kernel.size();
    int offset = d / 2;

    Image output(cols, rows, img.maxVal);

    for (int i = offset; i < rows - offset; i++) {
        for (int j = offset; j < cols - offset; j++) {

            float sum = 0.0f;

            for (int ki = -offset; ki <= offset; ki++) {
                for (int kj = -offset; kj <= offset; kj++) {

                    int pixel = img.pixels[i + ki][j + kj];
                    float k = kernel[ki + offset][kj + offset];

                    sum += pixel * k;
                }
            }

            int value = static_cast<int>(sum);

            // clamp para evitar underflow/overflow
            value = std::clamp(value, 0, img.maxVal);

            output.pixels[i][j] = value;
        }
    }

    return output;
}