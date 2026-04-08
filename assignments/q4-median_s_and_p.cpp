#include <filesystem>
#include <iostream>
#include <string>

#include "core/Image.hpp"
#include "io/ImageIO.hpp"
#include "processing/HistogramEq.hpp"

constexpr std::string images[] = {"images/input/bear_s_and_p.pgm", "images/input/boat_s_and_p.pgm",
                                  "images/input/glass_s_and_p.pgm"
                                  "images/input/lungs_s_and_p_10.pgm",
                                  "images/input/lungs_s_and_p_30.pgm", "images/input/lungs_s_and_p_50.pgm"};

void apply_median(const std::filesystem::path& img_path) {
    Image img = readImage(img_path.c_str());

    Image result = median<3>(img);

    std::filesystem::path out_path;
    for (auto path : img_path) {
        if (path.native() == "input") {
            out_path += "output";
        } else {
            out_path += path;
        }
    }

    std::cout << "writing image to: " << out_path.native() << std::endl;

    writeImage(out_path.c_str(), result);
}

int main() {
    for (const std::string& image : images) {
        apply_median(image);
    }
    std::cout << "Processamento concluido!\n";

    return 0;
}
