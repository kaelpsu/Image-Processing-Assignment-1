#include "processing/Filters.hpp"

std::vector<std::vector<float>> lowPass3x3() {
    return {
        {1/9.0, 1/9.0, 1/9.0},
        {1/9.0, 1/9.0, 1/9.0},
        {1/9.0, 1/9.0, 1/9.0}
    };
}

std::vector<std::vector<float>> highPass3x3() {
    return {
        {-1, -1, -1},
        {-1,  8, -1},
        {-1, -1, -1}
    };
}