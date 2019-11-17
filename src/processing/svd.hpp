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
        long U_height;
        long V_width;
        long rank;
        unsigned char max_value;
    };

    struct decomp
    {
        metadata meta;
        std::vector<half_float::half> U;
        std::vector<half_float::half> S;
        std::vector<half_float::half> V;
    };

    static decomp pgmSvdToHalfStream(std::istream &header, std::istream &pgm, int rank);

    static void writePgmAsSvd(const std::string &output_path, decomp decomposition);

    static std::tuple<std::string, long> svdToPGMString(const std::string &input_filename);
};
