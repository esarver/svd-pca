#include "svd.hpp"

#include <sstream>
#include <string>
#include <fstream>

#include <Eigen/SVD>

std::tuple<std::pair<int, int>, std::vector<f16>, std::vector<f16>, std::pair<int, int>, std::vector<f16>> SVD::pgmSvdToFloat16Stream(std::istream pgm, int rank)
{
    int line_count = 0;
    unsigned int width = 0;
    unsigned int height = 0;

    std::vector<double> original_values;

    for(std::string line; std::getline(pgm, line);line_count++) {
        if(line_count == 1)
        {
           std::stringstream ss(line);
           std::string width_string;
           std::string height_string;

           std::getline(ss, width_string, ' ');
           std::getline(ss, height_string, ' ');

           width = std::stoi(width_string);
           height = std::stoi(height_string);
        }
        else if(line_count >= 3) // We don't need the "max value" for our calculations.
        {
            std::stringstream ss(line);
            for(std::string value; std::getline(ss, value, ' ');)
            {
                original_values.push_back(std::stod(value));
            }
        }
    }

    Eigen::MatrixXd M(height, width);

    unsigned int column = 0;
    unsigned int row = 0;
    unsigned int count = 0;
    for(const auto &value: original_values)
    {
        M(row, column) = value;
        ++count;
        column = count % width;
        row = count / width;
    }

    Eigen::BDCSVD<Eigen::MatrixXd> svd(M, Eigen::ComputeFullU | Eigen::ComputeFullV);

    auto U = svd.matrixU();
    auto S = svd.singularValues();
    auto V = svd.matrixV();

    std::vector<f16> U_vec;
    std::vector<f16> S_vec;
    std::vector<f16> V_vec;

    for(unsigned int row = 0; row < U.rows(); row++)
    {
        for (unsigned int column = 0; column < U.cols(); column++)
        {
            double value = U(row, column);
            f16 half_p = doubleToF16(value);
            U_vec.push_back(half_p);
        }
    }

    for(unsigned int row = 0; row < S.rows(); row++)
    {
        for (unsigned int column = 0; column < S.cols(); column++)
        {
            double value = S(row, column);
            f16 half_p = doubleToF16(value);
            value = f16ToDouble(half_p);
            if(value > 0 || value < 0)
            {
                S_vec.push_back(half_p);
            }
        }
    }

    for(unsigned int row = 0; row < V.rows(); row++)
    {
        for (unsigned int column = 0; column < V.cols(); column++)
        {
            double value = V(row, column);
            f16 half_p = doubleToF16(value);
            V_vec.push_back(half_p);
        }
    }

    return {
        {U.rows(), U.cols()},
        U_vec,
        S_vec,
        {V.rows(), V.cols()},
        V_vec
    };

}

void SVD::writePgmAsSvd(const std::string &output_path, int U_width, int U_height, std::vector<f16> U, std::vector<f16> S, int V_width, int V_height, std::vector<f16> V)
{
    std::ofstream file(output_path);

    file << U_width << U_height;

    for(const auto &value : U)
    {
        file << value;
    }

    for (const auto &value : S)
    {
        file << value;
    }

    file << V_width << V_height;

    for (const auto &value : V)
    {
        file << value;
    }

    file.flush();
}

std::string SVD::svdToPGM(std::istream svd)
{

}
