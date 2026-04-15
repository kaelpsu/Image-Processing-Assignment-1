#include <iomanip>
#include <iostream>
#include <sstream>

#include "core/Image.hpp"
#include "io/ImageIO.hpp"
#include "processing/HCE.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_pet_image>\n";
        return 1;
    }

    std::string input_path = argv[1];
    Image img = readImage(input_path);

    if (img.width == 0 || img.height == 0) {
        std::cerr << "Fatal: Failed to load image or image dimensions are zero.\n";
        return 1;
    }

    double D0 = std::max(img.width, img.height) * 0.05;

    // Parameter sweep ranges
    std::vector<double> k1_vals = {0.5, 1.0, 1.5};
    std::vector<double> k2_vals = {1.0, 1.5, 2.0, 2.5};

    std::cout << "Starting High-Frequency Emphasis grid search...\n";
    std::cout << "Image size: " << img.width << "x" << img.height << " | D0: " << D0 << "\n";

    for (double k1 : k1_vals) {
        for (double k2 : k2_vals) {
            std::cout << "Processing k1 = " << k1 << ", k2 = " << k2 << "...\n";

            Image result = high_frequency_emphasis(img, k1, k2, D0);

            // Format output filename: result_k1_0.5_k2_1.5.pgm
            std::ostringstream filename;
            filename << "result_k1_" << std::fixed << std::setprecision(1) << k1 << "_k2_" << k2 << ".pgm";

            writeImage(filename.str(), result);
        }
    }

    std::cout << "Processing complete. Inspect the output directory to select the best configuration.\n";
    std::cout << "\"result_k1_1.0_k2_2.5.pgn\" appers to be the best.\n";
    return 0;
}
