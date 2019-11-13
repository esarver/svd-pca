#pragma once
#include <istream>
#include <vector>
#include <tuple>
#include <utility>
#include <include/half.hpp>

class SVD {
public:
    struct metadata
    {
        unsigned long U_width, U_height;
        unsigned long S_length;
        unsigned long V_width, V_height;
        unsigned char max_value;
    };

    struct decomp
    {
        metadata meta;
        std::vector<half_float::half> U;
        std::vector<half_float::half> S;
        std::vector<half_float::half> V;
    };

    static decomp pgmSvdToHalfStream(std::istream &pgm, int rank);

    static void writePgmAsSvd(const std::string &output_path, decomp decomposition);

    static std::string svdToPGM(const std::string &input_filename, const std::string &output_filename);
};
