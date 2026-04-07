#include "processing/HistogramEq.hpp"
#include "core/Image.hpp"
#include "io/ImageIO.hpp"
#include <iostream>

using namespace std;

int main() {
    Image img = readImage("images/input/Hill.png");

    Image result = histogramEqualization(img);

    writeImage("images/output/equalized.pgm", result);

    cout << "Processamento concluido!\n";

    return 0;
}