#include "Image.hpp"
#include "Filters.hpp"
#include "Convolution.hpp"
#include <iostream>

using namespace std;

int main() {
    // leitura
    Image image = Image::readPGM("images/input/bear_s_and_p.pgm");

    // filtros
    Image lowResult = convolve(image, lowPass3x3());
    Image highResult = convolve(image, highPass3x3());

    // saída
    lowResult.writePGM("images/output/lowpass.pgm");
    highResult.writePGM("images/output/highpass.pgm");

    cout << "Processamento concluido!\n";

    return 0;
}