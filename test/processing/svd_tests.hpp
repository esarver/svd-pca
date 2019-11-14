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
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(1.0f),
                  half_float::half(0.0f),
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
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(1.0f),
                  half_float::half(0.0f),

                  half_float::half(0.0787598f),
                  half_float::half(0.0711648f),
                  half_float::half(0.412309f),
                  half_float::half(0.904839f),
                  half_float::half(9.22747e-16f),
                  half_float::half(-2.89155e-15f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),
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
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(1.0f),
                  half_float::half(0.0f),

                  half_float::half(0.0787598f),
                  half_float::half(0.0711648f),
                  half_float::half(0.412309f),
                  half_float::half(0.904839f),
                  half_float::half(9.22747e-16f),
                  half_float::half(-2.89155e-15f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),

                  half_float::half(0.110067f),
                  half_float::half(0.211678f),
                  half_float::half(0.873538f),
                  half_float::half(-0.424275f),
                  half_float::half(-1.32019e-16f),
                  half_float::half(1.41098e-15f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),
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
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),
                  half_float::half(1.0f),
                  half_float::half(0.0f),

                  half_float::half(0.0787598f),
                  half_float::half(0.0711648f),
                  half_float::half(0.412309f),
                  half_float::half(0.904839f),
                  half_float::half(9.22747e-16f),
                  half_float::half(-2.89155e-15f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),

                  half_float::half(0.110067f),
                  half_float::half(0.211678f),
                  half_float::half(0.873538f),
                  half_float::half(-0.424275f),
                  half_float::half(-1.32019e-16f),
                  half_float::half(1.41098e-15f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),

                  half_float::half(0.596217f),
                  half_float::half(-0.150983f),
                  half_float::half(-0.0474702f),
                  half_float::half(-0.018391f),
                  half_float::half(0.766656f),
                  half_float::half(-0.177134f),
                  half_float::half(0.0f),
                  half_float::half(0.0f),
              };

    // Check Values
    EXPECT_EQ(decomposition.U, expected_U);
    EXPECT_EQ(decomposition.S, expected_S);
    EXPECT_EQ(decomposition.V, expected_V);
}
