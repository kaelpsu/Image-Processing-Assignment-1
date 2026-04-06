#include "Image.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Image::Image(int w, int h, int maxVal)
    : width(w), height(h), maxVal(maxVal),
      pixels(h, vector<int>(w, 0)) {}

static void skipComments(ifstream& file) {
    char ch;
    while (file >> ws && file.peek() == '#') {
        string line;
        getline(file, line);
    }
}

Image Image::readPGM(const std::string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Erro ao abrir arquivo: " << filename << "\n";
        exit(1);
    }

    string format;
    file >> format;

    if (format != "P2") {
        cerr << "Formato nao suportado (use P2)\n";
        exit(1);
    }

    skipComments(file);

    int width, height, maxVal;

    file >> width >> height;

    skipComments(file);

    file >> maxVal;

    Image img(width, height, maxVal);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            file >> img.pixels[i][j];
        }
    }

    return img;
}

void Image::writePGM(const std::string& filename) const {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Erro ao escrever arquivo: " << filename << "\n";
        return;
    }

    file << "P2\n";
    file << width << " " << height << "\n";
    file << maxVal << "\n";

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            file << pixels[i][j] << " ";
        }
        file << "\n";
    }
}