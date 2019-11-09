#pragma once
#include <istream>
#include <vector>
#include <tuple>
#include <utility>

#include "float16.hpp"
class SVD {
public:
    std::tuple<std::pair<int, int>, std::vector<f16>, std::vector<f16>, std::pair<int, int>, std::vector<f16>> pgmSvdToFloat16Stream(std::istream pgm, int rank);

    void writePgmAsSvd(const std::string &output_path, int U_width, int U_height, std::vector<f16> U, std::vector<f16> S, int V_width, int V_height, std::vector<f16> V);

    std::string svdToPGM(std::istream svd);
};
