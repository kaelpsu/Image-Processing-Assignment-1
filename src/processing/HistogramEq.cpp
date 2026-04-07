#include "processing/HistogramEq.hpp"
#include <vector>
#include <cmath>

using namespace std;

Image histogramEqualization(const Image& img) {
    int width = img.width;
    int height = img.height;
    int total = width * height;

    Image result(width, height, img.maxVal);

    // 1. Histograma
    vector<int> hist(256, 0);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            hist[img.pixels[i][j]]++;
        }
    }

    // 2. CDF
    vector<int> cdf(256, 0);
    cdf[0] = hist[0];

    for (int i = 1; i < 256; i++) {
        cdf[i] = cdf[i - 1] + hist[i];
    }

    // 3. Encontrar CDF_min (primeiro != 0)
    int cdf_min = 0;
    for (int i = 0; i < 256; i++) {
        if (cdf[i] != 0) {
            cdf_min = cdf[i];
            break;
        }
    }

    // 4. Criar LUT (tabela de transformação)
    vector<int> lut(256, 0);

    for (int i = 0; i < 256; i++) {
        lut[i] = round(
            ((float)(cdf[i] - cdf_min) / (total - cdf_min)) * 255.0f
        );

        if (lut[i] < 0) lut[i] = 0;
        if (lut[i] > 255) lut[i] = 255;
    }

    // 5. Aplicar transformação
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            result.pixels[i][j] = lut[img.pixels[i][j]];
        }
    }

    return result;
}