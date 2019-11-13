#include "gtest/gtest.h"

#include <climits>
#include <sstream>
#include <string>
#include "svd.hpp"

const std::string file_string = R"(P2
#Some comment.
8 8
255
0 0 0 0 0 0 0 0
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
    std::stringstream fake_file(file_string);

    SVD::decomp decomposition = SVD::pgmSvdToHalfStream(fake_file, 1);

    // Check meta information
    EXPECT_EQ(decomposition.meta.U_width, 1);
    EXPECT_EQ(decomposition.meta.U_height, 8);

    EXPECT_EQ(decomposition.meta.S_length, 1);

    EXPECT_EQ(decomposition.meta.V_width, 8);
    EXPECT_EQ(decomposition.meta.V_height, 1);

    // Check matrix information
    EXPECT_EQ(decomposition.U.size(), 8);
    EXPECT_EQ(decomposition.S.size(), 1);
    EXPECT_EQ(decomposition.V.size(), 8);

    std::vector<half_float::half> expected_U = {
                  half_float::half(0.0),
                  half_float::half(0.498331),
                  half_float::half(0.383043),
                  half_float::half(0.383043),
                  half_float::half(0.383043),
                  half_float::half(0.387861),
                  half_float::half(0.401327),
                  half_float::half(0.0)
              };

    std::vector<half_float::half> expected_S = {
                half_float::half(817.371)
              };

    std::vector<half_float::half> expected_V = {
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(1.0)
              };
    // Check Values
    EXPECT_EQ(decomposition.U, expected_U);
    EXPECT_EQ(decomposition.S, expected_S);
    EXPECT_EQ(decomposition.V, expected_V);
}

TEST(SVD, ProducesExpectedValuesRank2)
{
    std::stringstream fake_file(file_string);

    SVD::decomp decomposition = SVD::pgmSvdToHalfStream(fake_file, 2);

    // Check meta information
    EXPECT_EQ(decomposition.meta.U_width, 2);
    EXPECT_EQ(decomposition.meta.U_height, 8);

    EXPECT_EQ(decomposition.meta.S_length, 2);

    EXPECT_EQ(decomposition.meta.V_width, 8);
    EXPECT_EQ(decomposition.meta.V_height, 2);

    // Check matrix information
    EXPECT_EQ(decomposition.U.size(), 8 * 2);
    EXPECT_EQ(decomposition.S.size(), 2);
    EXPECT_EQ(decomposition.V.size(), 8 * 2);

    std::vector<half_float::half> expected_U = {
                  half_float::half(0.0),
                  half_float::half(0.498331),
                  half_float::half(0.383043),
                  half_float::half(0.383043),
                  half_float::half(0.383043),
                  half_float::half(0.387861),
                  half_float::half(0.401327),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.864596 ),
                  half_float::half(-0.23993 ),
                  half_float::half(-0.23993 ),
                  half_float::half(-0.23993 ),
                  half_float::half(-0.229162),
                  half_float::half(-0.165105),
                  half_float::half(0.0)
              };

    std::vector<half_float::half> expected_S = {
                half_float::half(817.371),
                half_float::half(330.45)
              };

    std::vector<half_float::half> expected_V = {
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(1.0),
                  half_float::half(0.0787598 ),
                  half_float::half(0.0711648 ),
                  half_float::half(-0.412309 ),
                  half_float::half(0.904839  ),
                  half_float::half(0),
                  half_float::half(0),
                  half_float::half(0),
                  half_float::half(0)
              };

    // Check Values
    EXPECT_EQ(decomposition.U, expected_U);
    EXPECT_EQ(decomposition.S, expected_S);
    EXPECT_EQ(decomposition.V, expected_V);
}

TEST(SVD, ProducesExpectedValuesRank3)
{
    std::stringstream fake_file(file_string);

    SVD::decomp decomposition = SVD::pgmSvdToHalfStream(fake_file, 3);

    // Check meta information
    EXPECT_EQ(decomposition.meta.U_width, 3);
    EXPECT_EQ(decomposition.meta.U_height, 8);

    EXPECT_EQ(decomposition.meta.S_length, 3);

    EXPECT_EQ(decomposition.meta.V_width, 8);
    EXPECT_EQ(decomposition.meta.V_height, 3);

    // Check matrix information
    EXPECT_EQ(decomposition.U.size(), 8 * 3);
    EXPECT_EQ(decomposition.S.size(), 3);
    EXPECT_EQ(decomposition.V.size(), 8 * 3);

    std::vector<half_float::half> expected_U = {
                  half_float::half(0.0),
                  half_float::half(0.498331),
                  half_float::half(0.383043),
                  half_float::half(0.383043),
                  half_float::half(0.383043),
                  half_float::half(0.387861),
                  half_float::half(0.401327),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.864596 ),
                  half_float::half(-0.23993 ),
                  half_float::half(-0.23993 ),
                  half_float::half(-0.23993 ),
                  half_float::half(-0.229162),
                  half_float::half(-0.165105),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0643104),
                  half_float::half(0.265503),
                  half_float::half(0.265503),
                  half_float::half(0.265503),
                  half_float::half(0.0459302),
                  half_float::half(-0.884465),
                  half_float::half(0.0)
              };

    std::vector<half_float::half> expected_S = {
                half_float::half(817.371),
                half_float::half(330.45),
                half_float::half(93.8889)
              };

    std::vector<half_float::half> expected_V = {
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(1.0),
                  half_float::half(0.0787598 ),
                  half_float::half(0.0711648 ),
                  half_float::half(-0.412309 ),
                  half_float::half(0.904839  ),
                  half_float::half(0),
                  half_float::half(0),
                  half_float::half(0),
                  half_float::half(0),
                  half_float::half(0.110067 ),
                  half_float::half(0.211678 ),
                  half_float::half(-0.873538),
                  half_float::half(-0.424275),
                  half_float::half(0),
                  half_float::half(0),
                  half_float::half(0),
                  half_float::half(0),
              };

    // Check Values
    EXPECT_EQ(decomposition.U, expected_U);
    EXPECT_EQ(decomposition.S, expected_S);
    EXPECT_EQ(decomposition.V, expected_V);
}

TEST(SVD, ProducesExpectedValuesRank4)
{
    std::stringstream fake_file(file_string);

    SVD::decomp decomposition = SVD::pgmSvdToHalfStream(fake_file, 4);

    // Check meta information
    EXPECT_EQ(decomposition.meta.U_width, 4);
    EXPECT_EQ(decomposition.meta.U_height, 8);

    EXPECT_EQ(decomposition.meta.S_length, 4);

    EXPECT_EQ(decomposition.meta.V_width, 8);
    EXPECT_EQ(decomposition.meta.V_height, 4);

    // Check matrix information
    EXPECT_EQ(decomposition.U.size(), 8 * 4);
    EXPECT_EQ(decomposition.S.size(), 4);
    EXPECT_EQ(decomposition.V.size(), 8 * 4);

    std::vector<half_float::half> expected_U = {
                  half_float::half(0.0),
                  half_float::half(0.498331),
                  half_float::half(0.383043),
                  half_float::half(0.383043),
                  half_float::half(0.383043),
                  half_float::half(0.387861),
                  half_float::half(0.401327),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.864596 ),
                  half_float::half(-0.23993 ),
                  half_float::half(-0.23993 ),
                  half_float::half(-0.23993 ),
                  half_float::half(-0.229162),
                  half_float::half(-0.165105),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0643104),
                  half_float::half(0.265503),
                  half_float::half(0.265503),
                  half_float::half(0.265503),
                  half_float::half(0.0459302),
                  half_float::half(-0.884465),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.00212611),
                  half_float::half(-0.241977),
                  half_float::half(-0.241977),
                  half_float::half(-0.241977),
                  half_float::half(0.891593),
                  half_float::half(-0.171459),
                  half_float::half(0.0),
              };

    std::vector<half_float::half> expected_S = {
                half_float::half(817.371),
                half_float::half(330.45),
                half_float::half(93.8889),
                half_float::half(39.911)
              };

    std::vector<half_float::half> expected_V = {
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(0.0),
                  half_float::half(1.0),
                  half_float::half(0.0787598 ),
                  half_float::half(0.0711648 ),
                  half_float::half(-0.412309 ),
                  half_float::half(0.904839  ),
                  half_float::half(0),
                  half_float::half(0),
                  half_float::half(0),
                  half_float::half(0),
                  half_float::half(0.110067 ),
                  half_float::half(0.211678 ),
                  half_float::half(-0.873538),
                  half_float::half(-0.424275),
                  half_float::half(0),
                  half_float::half(0),
                  half_float::half(0),
                  half_float::half(0),
                  half_float::half(0.596217),
                  half_float::half(-0.150983),
                  half_float::half(0.0474702),
                  half_float::half(-0.018391),
                  half_float::half(0),
                  half_float::half(0),
                  half_float::half(-0.786853),
                  half_float::half(0),
              };

    // Check Values
    EXPECT_EQ(decomposition.U, expected_U);
    EXPECT_EQ(decomposition.S, expected_S);
    EXPECT_EQ(decomposition.V, expected_V);
}
