#pragma once
#include <istream>
#include <vector>
#include <tuple>
#include <utility>
#include <include/half.hpp>

class SVD {
private:
    struct metadata
    {
        unsigned long U_width, U_height;
        unsigned long S_length;
        unsigned long V_width, V_height;
        unsigned char max_value;
    };
public:
    std::tuple<std::pair<int, int>, std::vector<half_float::half>, std::vector<half_float_half>, std::pair<int, int>, std::vector<half_float::half>> pgmSvdToHalfStream(std::istream pgm, int rank);

    void writePgmAsSvd(const std::string &output_path, unsigned long U_width, unsigned long U_height, std::vector<half_float::half> U, std::vector<half_float::half> S, unsigned long V_width, unsigned long V_height, std::vector<half_float::half> V);

    std::string svdToPGM(const std::string &input_filename, const std::string &output_filename);
};
