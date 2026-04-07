#include "io/ImageIO.hpp"
#include "io/PGM.hpp"
#include "io/PNG.hpp"

#include <stdexcept>

using namespace std;

static bool endsWith(const string& str, const string& suffix) {
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

Image readImage(const std::string& filename) {
    if (endsWith(filename, ".pgm")) {
        return readPGM(filename);
    }
    else if (endsWith(filename, ".png")) {
        return readPNG(filename);
    }

    throw runtime_error("Formato nao suportado");
}

void writeImage(const std::string& filename, const Image& img) {
    if (endsWith(filename, ".pgm")) {
        writePGM(filename, img);
        return;
    }
    else if (endsWith(filename, ".png")) {
        writePNG(filename, img);
        return;
    }

    throw runtime_error("Formato nao suportado");
}