#pragma once

#include <fftw3.h>

#include <algorithm>
#include <cmath>
#include <cstddef>

#include "core/Image.hpp"
#include "processing/HCE.hpp"

// D0 is the cutoff frequency for the underlying Gaussian High-Pass Filter
Image high_frequency_emphasis(const Image &input, double k1, double k2, double D0) {
    size_t width = input.width;
    size_t height = input.height;
    size_t total_pixels = width * height;

    fftw_complex *in = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * total_pixels);
    fftw_complex *out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * total_pixels);

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            size_t idx = i * width + j;
            in[idx][0] = static_cast<double>(input.pixels[i][j]);
            in[idx][1] = 0.0;
        }
    }

    // Forward 2D FFT
    fftw_plan forward_plan = fftw_plan_dft_2d(height, width, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(forward_plan);
    fftw_destroy_plan(forward_plan);

    // Apply High-Frequency Emphasis Filter: H_HFE(u,v) = k1 + k2 * H_HP(u,v)
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            double u = static_cast<double>(i < height / 2 ? i : i - height);
            double v = static_cast<double>(j < width / 2 ? j : j - width);

            double distance_sq = u * u + v * v;

            // Gaussian High-Pass Filter base
            double H_hp = 1.0 - std::exp(-distance_sq / (2.0 * D0 * D0));

            // Apply emphasis
            double H_hfe = k1 + k2 * H_hp;

            size_t idx = i * width + j;
            out[idx][0] *= H_hfe; // Real
            out[idx][1] *= H_hfe; // Imaginary
        }
    }

    // Inverse 2D FFT
    fftw_plan inverse_plan = fftw_plan_dft_2d(height, width, out, in, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(inverse_plan);
    fftw_destroy_plan(inverse_plan);

    Image result(width, height, input.maxVal);

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            size_t idx = i * width + j;
            double val = in[idx][0] / static_cast<double>(total_pixels);

            result.pixels[i][j] = std::clamp(static_cast<int>(std::round(val)), 0, input.maxVal);
        }
    }

    fftw_free(in);
    fftw_free(out);

    return result;
}
