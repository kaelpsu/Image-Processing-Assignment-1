#include "core/Image.hpp"
#include "processing/Filters.hpp"
#include "processing/Convolution.hpp"
#include "io/ImageIO.hpp"
#include <iostream>

using namespace std;

int main() {
    // leitura
    Image image = readImage("images/input/Google_JAX_low_contrast.pgm");

    // filtros
    Image lowResult = convolve(image, lowPass3x3());
    Image highResult = convolve(image, highPass3x3());

    // saída
    writeImage("images/output/lowpass.pgm", lowResult);
    writeImage("images/output/highpass.pgm", highResult);

    cout << "Processamento concluido!\n";

    return 0;
}