#include "io/PGM.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

static void skipComments(ifstream& file) {
    char ch;
    while (file >> ws && file.peek() == '#') {
        string line;
        getline(file, line);
    }
}

Image readPGM(const std::string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Erro ao abrir arquivo: " << filename << "\n";
        exit(1);
    }

    string format;
    file >> format;

    if (format != "P2" && format != "P5") {
        cerr << "Formato nao suportado (use P2 ou P5)\n";
        exit(1);
    }

    skipComments(file);

    int width, height, maxVal;

    file >> width >> height;

    skipComments(file);

    file >> maxVal;

    Image img(width, height, maxVal);

    if (format == "P2") {
        // ASCII
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                file >> img.pixels[i][j];
            }
        }
    } else {
        // P5 (binário)
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                unsigned char value;
                file.read(reinterpret_cast<char*>(&value), 1);
                img.pixels[i][j] = static_cast<int>(value);
            }
        }
    }

    return img;
}

void writePGM(const std::string& filename, const Image& img) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Erro ao escrever arquivo: " << filename << "\n";
        return;
    }

    file << "P2\n";
    file << img.width << " " << img.height << "\n";
    file << img.maxVal << "\n";

    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            int clampedValue = std::clamp(img.pixels[i][j], 0, img.maxVal);
            file << clampedValue << " ";
        }
        file << "\n";
    }
}