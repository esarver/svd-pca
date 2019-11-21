#include "svd.hpp"

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(' ');
     if (std::string::npos == first)
     {
         return str;
     }
     size_t last = str.find_last_not_of(' ');
     return str.substr(first, (last - first + 1));
}

SVD::decomp SVD::pgmSvdToHalfStream(std::istream &header, std::istream &pgm, int rank)
{
    int line_count = 0;
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned char max_value = 0;

    std::vector<double> original_values;

    for(std::string line; std::getline(header, line);line_count++) {
        if(line.find('#') != std::string::npos
            || line.find('P') != std::string::npos)
        {
            line_count--;
            continue;
        }
        if(line_count == 0)
        {
           std::stringstream ss(line);
           std::string width_string;
           std::string height_string;

           std::getline(ss, height_string, ' ');
           std::getline(ss, width_string, ' ');

           width = std::stoi(trim(width_string));
           height = std::stoi(trim(height_string));
        }
        else if (line_count == 1)
        {
            max_value = std::stoi(line);
        }
    }
    for(std::string line; std::getline(pgm, line);)
    {
        std::stringstream ss(line);
        for(std::string value; std::getline(ss, value, ' ');)
        {
            if(trim(value).length() > 0)
            {
                original_values.push_back(std::stoi(trim(value)));
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

    M /= max_value;

    Eigen::BDCSVD<Eigen::MatrixXd> svd(M, Eigen::ComputeFullU | Eigen::ComputeFullV);

    auto U = svd.matrixU();
    auto S = svd.singularValues();
    auto V = svd.matrixV();
//    std::cout << "M:" << std::endl << M << std::endl;
//    std::cout << "U:" << std::endl << U << std::endl;
    std::cout << "S:" << std::endl << S << std::endl;
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
        S_vec.push_back(half_p);
    }

    for (unsigned int column = 0; column < rank; column++)
    {
        for(unsigned int row = 0; row < V.rows(); row++)
        {
            double value = V(row, column);
            half_float::half half_p = half_float::half_cast<half_float::half>(value);
            V_vec.push_back(half_p);
        }
    }

    return {
        {
            U.rows(),
            V.rows(),
            rank,
            max_value
        },
        U_vec,
        S_vec,
        V_vec
    };

}

SVD::decomp SVD::rankDecomp(const Eigen::MatrixXd &U, const Eigen::MatrixXd &S, const Eigen::MatrixXd &V, int rank, unsigned char max_value)
{

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
        S_vec.push_back(half_p);
    }

    for (unsigned int column = 0; column < rank; column++)
    {
        for(unsigned int row = 0; row < V.rows(); row++)
        {
            double value = V(row, column);
            half_float::half half_p = half_float::half_cast<half_float::half>(value);
            V_vec.push_back(half_p);
        }
    }

    return {
        {
            U.rows(),
            V.rows(),
            rank,
            max_value
        },
        U_vec,
        S_vec,
        V_vec
    };
}

void SVD::writeAllDecomps(std::istream &header, std::istream &pgm, const std::string &filename)
{
    int line_count = 0;
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned char max_value = 0;

    std::vector<double> original_values;

    for(std::string line; std::getline(header, line);line_count++) {
        if(line.find('#') != std::string::npos
            || line.find('P') != std::string::npos)
        {
            line_count--;
            continue;
        }
        if(line_count == 0)
        {
           std::stringstream ss(line);
           std::string width_string;
           std::string height_string;

           std::getline(ss, height_string, ' ');
           std::getline(ss, width_string, ' ');

           width = std::stoi(trim(width_string));
           height = std::stoi(trim(height_string));
        }
        else if (line_count == 1)
        {
            max_value = std::stoi(trim(line));
        }
    }
    for(std::string line; std::getline(pgm, line);)
    {
        std::stringstream ss(line);
        for(std::string value; std::getline(ss, value, ' ');)
        {
            if(trim(value).length() > 0)
            {
                original_values.push_back(std::stoi(trim(value)));
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

    M /= max_value;

    Eigen::BDCSVD<Eigen::MatrixXd> svd(M, Eigen::ComputeFullU | Eigen::ComputeFullV);

    auto U = svd.matrixU();
    auto S = svd.singularValues();
    auto V = svd.matrixV();

    unsigned int max_rank = std::min(height, width);

    for(unsigned int r = 1; r <= max_rank; r++)
    {
        SVD::writePgmAsSvd(filename + "_" + std::to_string(r), rankDecomp(U, S, V, r, max_value));
        std::cout << "Compressed " << r << " of " << max_rank << std::endl;
    }

    for(unsigned int r = 1; r <= max_rank; r++)
    {
        auto [text, rank] = SVD::svdToPGMString(filename + "_" + std::to_string(r));
        std::ofstream out(filename + "_" + std::to_string(r) + ".pgm");
        out << text;
        out.flush();
        out.close();
        std::cout << "Decompressed " << r << " of " << max_rank << std::endl;
    }

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

std::tuple<std::string, long> SVD::svdToPGMString(const std::string &input_filename)
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
    Eigen::MatrixXd U = Eigen::MatrixXd::Zero(sizes->U_height, sizes->U_height);
    Eigen::MatrixXd S = Eigen::MatrixXd::Zero(sizes->U_height, sizes->V_width);
    Eigen::MatrixXd V = Eigen::MatrixXd::Zero(sizes->V_width, sizes->V_width);
    long count = 0;
    for(const auto &value: values)// TODO ensure correct order...
    {
        if(count < (U_size))
        {
            long row = count%sizes->U_height;
            long col = (count < sizes->U_height)? 0 : (count)/sizes->U_height;
//            std::cout << "U(" << row << ", " << col << ")" <<std::endl;
            U(row, col) = half_float::half_cast<double>(value);

        }
        else if(count < (U_size) + sizes->rank )
        {
            S(count - U_size, count - U_size) = half_float::half_cast<double>(value);
        }
        else
        {
            long v_count = count - (U_size + sizes->rank);
            long row = v_count%sizes->V_width;
            long col = (count < sizes->V_width) ? 0 : (v_count)/sizes->V_width;
//            std::cout << "V(" << row << ", " << col << ")" <<std::endl;
            V(row, col) = half_float::half_cast<double>(value);
        }
        count++;
    }
//    std::cout << "U: " << std::endl << U << std::endl;
//    std::cout << "S: " << std::endl << S << std::endl;
//    std::cout << "V: " << std::endl << V << std::endl;

    Eigen::MatrixXd pgm_approx = U * (S * V.transpose());
    pgm_approx *= sizes->max_value;

//    std::cout << "APPROXIMATED PICTURE" << std::endl << pgm_approx << std::endl;

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
            else if (value < 0)
            {
                value = 0;
            }

            pgm_values.push_back((unsigned char)value);
        }
    }

    std::stringstream out;
    out << "P2" << std::endl;
    out << std::to_string(height) << " " << std::to_string(width) << std::endl;
    out << std::to_string(sizes->max_value) << std::endl;

    int val_count = 0;
    for(const auto &value: pgm_values)
    {
        out << std::to_string(value);
        if(val_count > 20)
        {
            val_count = -1;
            out << std::endl;
        }
        else
        {
            out << " ";
        }
        val_count++;
    }

    out.flush();
    return {out.str(), sizes->rank};
}
