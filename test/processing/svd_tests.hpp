#include "gtest/gtest.h"

#include <climits>
#include <sstream>
#include <string>
#include "svd.hpp"

const std::string header_string = R"(P2
#Some comment.
8 8
255)";

const std::string pgm_string = R"(0 0 0 0 0 0 0 0
0 50 100 200 255 255 255 0
0 0 0 200 255 0 0 0
0 0 0 200 255 0 0 0
0 0 0 200 255 0 0 0
0 50 0 200 255 0 0 0
0 50 100 200 255 0 0 0
0 0 0 0 0 0 0 0
)";

TEST(SVD, ProducesExpectedValuesRank1)
{
    std::stringstream header(header_string);
    std::stringstream pgm(pgm_string);

    SVD::decomp decomposition = SVD::pgmSvdToHalfStream(header, pgm, 1);

    // Check meta information
    EXPECT_EQ(decomposition.meta.U_height, 8);
    EXPECT_EQ(decomposition.meta.V_width, 8);
    EXPECT_EQ(decomposition.meta.rank, 1);

    // Check matrix information
    EXPECT_EQ(decomposition.U.size(), 8);
    EXPECT_EQ(decomposition.S.size(), 1);
    EXPECT_EQ(decomposition.V.size(), 8);

    std::vector<half_float::half> expected_U = {
                  half_float::half(0.0f),
                  half_float::half(0.498331f),
                  half_float::half(0.383043f),
                  half_float::half(0.383043f),
                  half_float::half(0.383043f),
                  half_float::half(0.387861f),
                  half_float::half(0.401327f),
                  half_float::half(0.0f),
              };

    std::vector<half_float::half> expected_S = {
                half_float::half(817.371f),
              };

    std::vector<half_float::half> expected_V = {
                half_float::half(       0.0f),
                half_float::half( 0.0787598f),
                half_float::half(  0.110067f),
                half_float::half(  0.596217f),
                half_float::half(  0.760176f),
                half_float::half(  0.155467f),
                half_float::half(  0.155467f),
                half_float::half(       0.0f),
              };

    // Check Values
    EXPECT_EQ(decomposition.U, expected_U);
    EXPECT_EQ(decomposition.S, expected_S);
    EXPECT_EQ(decomposition.V, expected_V);
}

TEST(SVD, ProducesExpectedValuesRank2)
{
    std::stringstream header(header_string);
    std::stringstream pgm(pgm_string);

    SVD::decomp decomposition = SVD::pgmSvdToHalfStream(header, pgm, 2);

    // Check meta information
    EXPECT_EQ(decomposition.meta.U_height, 8);
    EXPECT_EQ(decomposition.meta.V_width, 8);
    EXPECT_EQ(decomposition.meta.rank, 2);

    // Check matrix information
    EXPECT_EQ(decomposition.U.size(), 8 * 2);
    EXPECT_EQ(decomposition.S.size(), 2);
    EXPECT_EQ(decomposition.V.size(), 8 * 2);

    std::vector<half_float::half> expected_U = {
                  half_float::half(0.0f),
                  half_float::half(0.498331f),
                  half_float::half(0.383043f),
                  half_float::half(0.383043f),
                  half_float::half(0.383043f),
                  half_float::half(0.387861f),
                  half_float::half(0.401327f),
                  half_float::half(0.0f),

                  half_float::half(0.0f),
                  half_float::half(0.864596f),
                  half_float::half(-0.23993f),
                  half_float::half(-0.23993f),
                  half_float::half(-0.23993f),
                  half_float::half(-0.229162f),
                  half_float::half(-0.165105f),
                  half_float::half(0.0f),
              };

    std::vector<half_float::half> expected_S = {
                half_float::half(817.371f),
                half_float::half(330.45f),
              };

    std::vector<half_float::half> expected_V = {
                half_float::half(       0.0f),
                half_float::half( 0.0787598f),
                half_float::half(  0.110067f),
                half_float::half(  0.596217f),
                half_float::half(  0.760176f),
                half_float::half(  0.155467f),
                half_float::half(  0.155467f),
                half_float::half(       0.0f),

                half_float::half(      0.0f),
                half_float::half(0.0711648f),
                half_float::half( 0.211678f),
                half_float::half(-0.150983f),
                half_float::half(-0.192503f),
                half_float::half( 0.667186f),
                half_float::half( 0.667186f),
                half_float::half(      0.0f),
              };

    // Check Values
    EXPECT_EQ(decomposition.U, expected_U);
    EXPECT_EQ(decomposition.S, expected_S);
    EXPECT_EQ(decomposition.V, expected_V);
}

TEST(SVD, ProducesExpectedValuesRank3)
{
    std::stringstream header(header_string);
    std::stringstream pgm(pgm_string);

    SVD::decomp decomposition = SVD::pgmSvdToHalfStream(header, pgm, 3);

    // Check meta information
    EXPECT_EQ(decomposition.meta.U_height, 8);
    EXPECT_EQ(decomposition.meta.V_width, 8);
    EXPECT_EQ(decomposition.meta.rank, 3);

    // Check matrix information
    EXPECT_EQ(decomposition.U.size(), 8 * 3);
    EXPECT_EQ(decomposition.S.size(), 3);
    EXPECT_EQ(decomposition.V.size(), 8 * 3);

    std::vector<half_float::half> expected_U = {
                  half_float::half(0.0f),
                  half_float::half(0.498331f),
                  half_float::half(0.383043f),
                  half_float::half(0.383043f),
                  half_float::half(0.383043f),
                  half_float::half(0.387861f),
                  half_float::half(0.401327f),
                  half_float::half(0.0f),

                  half_float::half(0.0f),
                  half_float::half(0.864596f),
                  half_float::half(-0.23993f),
                  half_float::half(-0.23993f),
                  half_float::half(-0.23993f),
                  half_float::half(-0.229162f),
                  half_float::half(-0.165105f),
                  half_float::half(0.0f),

                  half_float::half(0.0f),
                  half_float::half(-0.0643104f),
                  half_float::half(-0.265503f),
                  half_float::half(-0.265503f),
                  half_float::half(-0.265503f),
                  half_float::half(-0.0459302f),
                  half_float::half(0.884465f),
                  half_float::half(0.0f),
              };

    std::vector<half_float::half> expected_S = {
                half_float::half(817.371f),
                half_float::half(330.45f),
                half_float::half(93.8889f),
              };

    std::vector<half_float::half> expected_V = {
                half_float::half(       0.0f),
                half_float::half( 0.0787598f),
                half_float::half(  0.110067f),
                half_float::half(  0.596217f),
                half_float::half(  0.760176f),
                half_float::half(  0.155467f),
                half_float::half(  0.155467f),
                half_float::half(       0.0f),

                half_float::half(      0.0f),
                half_float::half(0.0711648f),
                half_float::half( 0.211678f),
                half_float::half(-0.150983f),
                half_float::half(-0.192503f),
                half_float::half( 0.667186f),
                half_float::half( 0.667186f),
                half_float::half(      0.0f),

                half_float::half(       0.0f),
                half_float::half(  0.412309f),
                half_float::half(  0.873538f),
                half_float::half(-0.0474702f),
                half_float::half(-0.0605245f),
                half_float::half( -0.174666f),
                half_float::half( -0.174666f),
                half_float::half(       0.0f),
              };

    // Check Values
    EXPECT_EQ(decomposition.U, expected_U);
    EXPECT_EQ(decomposition.S, expected_S);
    EXPECT_EQ(decomposition.V, expected_V);
}

TEST(SVD, ProducesExpectedValuesRank4)
{
    std::stringstream header(header_string);
    std::stringstream pgm(pgm_string);

    SVD::decomp decomposition = SVD::pgmSvdToHalfStream(header, pgm, 4);

    // Check meta information
    EXPECT_EQ(decomposition.meta.U_height, 8);
    EXPECT_EQ(decomposition.meta.V_width, 8);
    EXPECT_EQ(decomposition.meta.rank, 4);

    // Check matrix information
    EXPECT_EQ(decomposition.U.size(), 8 * 4);
    EXPECT_EQ(decomposition.S.size(), 4);
    EXPECT_EQ(decomposition.V.size(), 8 * 4);

    std::vector<half_float::half> expected_U = {
                  half_float::half(0.0f),
                  half_float::half(0.498331f),
                  half_float::half(0.383043f),
                  half_float::half(0.383043f),
                  half_float::half(0.383043f),
                  half_float::half(0.387861f),
                  half_float::half(0.401327f),
                  half_float::half(0.0f),

                  half_float::half(0.0f),
                  half_float::half(0.864596f),
                  half_float::half(-0.23993f),
                  half_float::half(-0.23993f),
                  half_float::half(-0.23993f),
                  half_float::half(-0.229162f),
                  half_float::half(-0.165105f),
                  half_float::half(0.0f),

                  half_float::half(0.0f),
                  half_float::half(-0.0643104f),
                  half_float::half(-0.265503f),
                  half_float::half(-0.265503f),
                  half_float::half(-0.265503f),
                  half_float::half(-0.0459302f),
                  half_float::half(0.884465f),
                  half_float::half(0.0f),

                  half_float::half(0.0f),
                  half_float::half(0.00212611f),
                  half_float::half(-0.241977f),
                  half_float::half(-0.241977f),
                  half_float::half(-0.241977f),
                  half_float::half(0.891593f),
                  half_float::half(-0.171459f),
                  half_float::half(0.0f),
              };

    std::vector<half_float::half> expected_S = {
                half_float::half(817.371f),
                half_float::half(330.45f),
                half_float::half(93.8889f),
                half_float::half(39.911f)
              };

    std::vector<half_float::half> expected_V = {
                half_float::half(       0.0f),
                half_float::half( 0.0787598f),
                half_float::half(  0.110067f),
                half_float::half(  0.596217f),
                half_float::half(  0.760176f),
                half_float::half(  0.155467f),
                half_float::half(  0.155467f),
                half_float::half(       0.0f),

                half_float::half(      0.0f),
                half_float::half(0.0711648f),
                half_float::half( 0.211678f),
                half_float::half(-0.150983f),
                half_float::half(-0.192503f),
                half_float::half( 0.667186f),
                half_float::half( 0.667186f),
                half_float::half(      0.0f),

                half_float::half(       0.0f),
                half_float::half(  0.412309f),
                half_float::half(  0.873538f),
                half_float::half(-0.0474702f),
                half_float::half(-0.0605245f),
                half_float::half( -0.174666f),
                half_float::half( -0.174666f),
                half_float::half(       0.0f),

                half_float::half(       0.0f),
                half_float::half(  0.904839f),
                half_float::half( -0.424275f),
                half_float::half( -0.018391f),
                half_float::half(-0.0234485f),
                half_float::half( 0.0135842f),
                half_float::half( 0.0135842f),
                half_float::half(       0.0f),
            };

    // Check Values
    EXPECT_EQ(decomposition.U, expected_U);
    EXPECT_EQ(decomposition.S, expected_S);
    EXPECT_EQ(decomposition.V, expected_V);
}

TEST(SVD, GeneratesPgmFromSVDRank4)
{
    std::stringstream header(header_string);
    std::stringstream pgm(pgm_string);

    SVD::decomp decomposition = SVD::pgmSvdToHalfStream(header, pgm, 4);

    std::string svd_filepath = "/tmp/SVD_TEST_RANK4.pgm.SVD";
    SVD::writePgmAsSvd(svd_filepath, decomposition);

    auto [gen_pgm_string, rank] = SVD::svdToPGMString(svd_filepath);

    std::string expected_pgm = R"(P2
8 8
255
0 0 0 0 0 0 0 0 0 50 100 200 255 255 255 0 0 0 0 200 255 0
0 0 0 0 0 200 255 0 0 0 0 0 0 200 255 0 0 0 0 50 0 200
255 0 0 0 0 50 100 200 255 0 0 0 0 0 0 0 0 0 0 0 )";

    EXPECT_EQ(gen_pgm_string, expected_pgm);
    EXPECT_EQ(rank, 4);
}

TEST(SVD, GeneratesPgmFromSVDRank8)
{
    std::stringstream header(header_string);
    std::stringstream pgm(pgm_string);

    SVD::decomp decomposition = SVD::pgmSvdToHalfStream(header, pgm, 8);

    std::string svd_filepath = "/tmp/SVD_TEST_RANK8.pgm.SVD";
    SVD::writePgmAsSvd(svd_filepath, decomposition);

    auto [gen_pgm_string, rank] = SVD::svdToPGMString(svd_filepath);

    std::string expected_pgm = R"(P2
8 8
255
0 0 0 0 0 0 0 0 0 50 100 200 255 255 255 0 0 0 0 200 255 0
0 0 0 0 0 200 255 0 0 0 0 0 0 200 255 0 0 0 0 50 0 200
255 0 0 0 0 50 100 200 255 0 0 0 0 0 0 0 0 0 0 0 )";

    EXPECT_EQ(gen_pgm_string, expected_pgm);
    EXPECT_EQ(rank, 8);
}

TEST(SVD, SquigleTest)
{
    std::string hstring = R"(P2
5 3
255)";
    std::string pstring = R"(50 0 0 0 0
0 100 0 200 0
0 0 150 0 250
)";
    std::stringstream header(hstring);
    std::stringstream pgm(pstring);

    SVD::decomp decomposition = SVD::pgmSvdToHalfStream(header, pgm, 3);

    std::string svd_filepath = "/tmp/SVD_TEST_RANK4.pgm.SVD";
    SVD::writePgmAsSvd(svd_filepath, decomposition);

    auto [gen_pgm_string, rank] = SVD::svdToPGMString(svd_filepath);

    std::string expected_pgm = R"(P2
5 3
255
50 0 0 0 0 0 100 0 200 0 0 0 150 0 250 )";

    EXPECT_EQ(gen_pgm_string, expected_pgm);
    EXPECT_EQ(rank, 3);
}
