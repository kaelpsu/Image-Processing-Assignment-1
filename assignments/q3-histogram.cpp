#include "processing/HistogramEq.hpp"
#include "core/Image.hpp"
#include "io/ImageIO.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Erro: Número incorreto de argumentos.\n";
        cerr << "Uso correto: " << argv[0] << " <input_file>\n";
        return 1;
    }

    string inputFile = argv[1];
    string outputFile = inputFile;

    // Extract only the filename
    size_t slashPos = inputFile.find_last_of("/\\");
    string pureFilename = (slashPos == string::npos) ? inputFile : inputFile.substr(slashPos + 1);

    // 2. Separate the base name from the extension
    size_t dotPos = pureFilename.find_last_of(".");
    string baseName = (dotPos == string::npos) ? pureFilename : pureFilename.substr(0, dotPos);
    string extension = ".pgm"; // default extension

    string outDir = "images/output/";
    string out = outDir + baseName + "_equalized" + extension;

    try {
        cout << "Lendo imagem: " << inputFile << "...\n";
        Image img = readImage(inputFile);

        cout << "Equalizando histograma...\n";
        Image result = histogramEqualization(img);

        cout << "Salvando resultado...\n";
        writeImage(out, result);

        cout << "Processamento concluido!\n";
        cout << "-> " << out << "\n";
    
    } catch (const exception& e) {
        cerr << "Erro: " << e.what() << "\n";
        return 1;
    }

    return 0;
}