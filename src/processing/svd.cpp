#include "svd.hpp"

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

#include <Eigen/SVD>

SVD::decomp SVD::pgmSvdToHalfStream(std::istream &pgm, int rank)
{
    int line_count = 0;
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned char max_value = 0;

    std::vector<double> original_values;

    for(std::string line; std::getline(pgm, line);line_count++) {
        if(line.find('#') != std::string::npos)
        {
            line_count--;
            continue;
        }
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
        else if (line_count == 2)
        {
            max_value = std::stoi(line);
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

//    std::cout << "U:" << std::endl << U << std::endl;
//    std::cout << "S:" << std::endl << S << std::endl;
//    std::cout << "V:" << std::endl << V << std::endl;

    std::vector<half_float::half> U_vec;
    std::vector<half_float::half> S_vec;
    std::vector<half_float::half> V_vec;

    for (unsigned int column = 0; column < rank; column++)
    {
        for(unsigned int row = 0; row < U.rows(); row++)
        {
            double value = U(row, column);
            half_float::half half_p = half_float::half_cast<half_float::half>(value);
            U_vec.push_back(half_p);
        }
    }

    for(unsigned int row = 0; row < rank; row++)
    {
        double value = S(row, 0);
        half_float::half half_p = half_float::half_cast<half_float::half>(value);
        if(half_p > 0 || half_p < 0)
        {
            S_vec.push_back(half_p);
        }
    }

    for(unsigned int row = 0; row < rank; row++)
    {
        for (unsigned int column = 0; column < V.cols(); column++)
        {
            double value = V(row, column);
            half_float::half half_p = half_float::half_cast<half_float::half>(value);
            V_vec.push_back(half_p);
        }
    }

    return {
        {
            U.rows(),
            V.cols(),
            rank,
            max_value
        },
        U_vec,
        S_vec,
        V_vec
    };

}

void SVD::writePgmAsSvd(const std::string &output_path, decomp decomposition)
{
    std::ofstream file(output_path, std::ios::out | std::ios::binary);

    file.write((char*)&(decomposition.meta), sizeof (metadata));

    for(const auto &value : decomposition.U)
    {
        file.write((char*)&value, sizeof (half_float::half));
    }

    for (const auto &value : decomposition.S)
    {
        file.write((char*)&value, sizeof (half_float::half));
    }

    for (const auto &value : decomposition.V)
    {
        file.write((char*)&value, sizeof (half_float::half));
    }

    file.flush();

    file.close();
}

std::string SVD::svdToPGM(const std::string &input_filename, const std::string &output_filename)
{
    std::ifstream file(input_filename, std::ios::in | std::ios::binary);

    metadata *sizes = new metadata;

    file.read((char*)sizes, sizeof (metadata));

    std::vector<half_float::half> values;
    half_float::half temp;
    while(file.read((char*)&temp, sizeof(half_float::half)))
    {
        values.push_back(temp);
    }

    file.close();

    // Calculate approximated PGM
    unsigned long U_size =  sizes->rank * sizes->U_height;
    unsigned long V_size = sizes->V_width * sizes->rank;
    Eigen::MatrixXd U(sizes->U_height, sizes->rank);
    Eigen::MatrixXd S(sizes->V_width, sizes->U_height);
    Eigen::MatrixXd V(sizes->rank, sizes->V_width);
    unsigned long count = 0;
    for(const auto &value: values)
    {
        if(count < (U_size))
        {
            U(count%sizes->rank, count/sizes->rank) = half_float::half_cast<double>(value);

        }
        else if(count < (U_size) + sizes->rank )
        {
            S(count - U_size, count - U_size) = half_float::half_cast<double>(value);
        }
        else if(count < (U_size + sizes->rank) + V_size)
        {
            unsigned long v_count = count - (U_size + sizes->rank);
            S(v_count % sizes->V_width, v_count / sizes->V_width) = half_float::half_cast<double>(value);
        }
    }

    Eigen::MatrixXd pgm_approx = U * S * V.transpose();

    // round to nearest integer value and get other info.
    unsigned long width = pgm_approx.cols();
    unsigned long height = pgm_approx.rows();

    std::vector<unsigned char> pgm_values;

    for(unsigned int row = 0; row < pgm_approx.rows(); row++)
    {
        for (unsigned int column = 0; column < pgm_approx.cols(); column++)
        {
            long value = std::lround(pgm_approx(row, column));
            if(value > UCHAR_MAX)
            {
                value = UCHAR_MAX;
            }

            pgm_values.push_back((unsigned char)value);
        }
    }

    std::ofstream out(output_filename, std::ios::out);
    out << "P2" << std::endl;
    out << width << " " << height << std::endl;
    out << sizes->max_value << std::endl;

    int val_count = 0;
    for(const auto &value: pgm_values)
    {
        out << value << " ";
        if(val_count > 20)
        {
            val_count = -1;
            out << std::endl;
        }
        val_count++;
    }

    out.flush();
    out.close();
}
