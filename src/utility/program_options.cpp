#include "program_options.hpp"

#include <unistd.h>
#include <climits>
#include <getopt.h>
#include <iostream>
#include <sstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

ProgramOptions* ProgramOptions::s_instance = nullptr;

ProgramOptions* ProgramOptions::instance()
{
    if(s_instance == nullptr)
    {
        s_instance = new ProgramOptions();
    }

    return s_instance;
}

ProgramOptions::AlgorithmSelection ProgramOptions::selected_algorithm()
{
    return instance()->m_algorithm;
}

const std::string& ProgramOptions::program_name()
{
    return instance()->m_program_name;
}

const std::string& ProgramOptions::text_pgm_filepath()
{
    return instance()->m_text_pgm_filepath;
}

const std::string& ProgramOptions::binary_pgm_filepath()
{
    return instance()->m_binary_pgm_filepath;
}

const std::string& ProgramOptions::pgm_header_filepath()
{
    return instance()->m_pgm_header_filepath;
}

const std::string& ProgramOptions::svd_matrices_filepath()
{
    return instance()->m_svd_matrices_filepath;
}

int ProgramOptions::approximation_rank()
{
    return instance()->m_approximation_rank;
}

void ProgramOptions::clear()
{
    if(s_instance)
    {
        delete s_instance;
    }
    s_instance = new ProgramOptions();
}

void ProgramOptions::print_help()
{
    //TODO UPDATE THIS!
    std::cout << std::endl;
    std::cout << " Usage: " << instance()->m_program_name << " [1|2|3|4] [pgm-file|pgm-header-file|SVD-compressed-file]" << std::endl;
    std::cout << "                                   [SVD-matrices-file] [approximation-rank]" << std::endl;
    std::cout << std::endl;
    std::cout << " Advance Algorithms Project #2: Image Compression Using SVD and Dimensionality" << std::endl;
    std::cout << "                                  Reduction Using PCA" << std::endl;
    std::cout << std::endl;
    std::cout << " One and only one of the following parameters must be selected." << std::endl;
    std::cout << "     1                   Convert ASCII PGM file to a binary PGM file." << std::endl;
    std::cout << "                              Requires: pgm-file (ASCII)" << std::endl;
    std::cout << "                              Outputs:  pgm-file (binary)" << std::endl;
    std::cout << std::endl;
    std::cout << "     2                   Convert a binary PGM file to an ASCII PGM file." << std::endl;
    std::cout << "                              Requires: pgm-file (binary)" << std::endl;
    std::cout << "                              Outputs:  pgm-file (ASCII)" << std::endl;
    std::cout << std::endl;
    std::cout << "     3                   Store a compressed image file using SVD approximation" << std::endl;
    std::cout << "                              Requires: pgm-header-file (ASCII)," << std::endl;
    std::cout << "                                        SVD-matrices-file," << std::endl;
    std::cout << "                                        approximation-rank" << std::endl;
    std::cout << "                              Outputs:  SVD-compressed-file" << std::endl;
    std::cout << std::endl;
    std::cout << "     4                   Revert an SVD-compressed image to a binary pgm-file" << std::endl;
    std::cout << "                              Requires: SVD-compressed-file" << std::endl;
    std::cout << "                              Outputs:  pgm-header-file (ASCII)," << std::endl;
    std::cout << "                                        SVD-matrices-file," << std::endl;
    std::cout << "                                        pgm-file (binary)" << std::endl;
    std::cout << std::endl;
    std::cout << "     5                   Create a randomly generated PGM image to the given file" << std::endl;
    std::cout << "                              Requires: pgm-file" << std::endl;
    std::cout << "                              Outputs:  pgm-file (ASCII)," << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << " The following options are required as stated above:" << std::endl;
    std::cout << "    pgm-file (ASCII)     Textual PGM file conforming to the" << std::endl;
    std::cout << "                           PGM P2 specification" << std::endl;
    std::cout << std::endl;
    std::cout << "    pgm-file (binary)    Binary PGM file conforming to the" << std::endl;
    std::cout << "                           PGM P2 specification" << std::endl;
    std::cout << std::endl;
    std::cout << "    pgm-header-file      Text file containing the PGM P2 specification header" << std::endl;
    std::cout << "                           (width height max-value)" << std::endl;
    std::cout << std::endl;
    std::cout << "    SVD-compressed-file  File that has been approximated using SVD" << std::endl;
    std::cout << std::endl;
    std::cout << "    SVD-matrices-file    File containing U, \u03A3, and V matrices" << std::endl;
    std::cout << std::endl;
    std::cout << "    approximation-rank   An integer representing the rank of the approximation" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << " AUTHORS:" << std::endl;
    std::cout << "          Quansu Lu    <ql21@zips.uakron.edu>" << std::endl;
    std::cout << "       Edwin Sarver    <els40@zips.uakron.edu>" << std::endl;
    std::cout << "          Ying Wang    <yw73@zips.uakron.edu>" << std::endl;

}

void ProgramOptions::parse(int argc, char** argv)
{
    //TODO UPDATE THIS!
    optind = 1; // reset getopt()
    opterr = 0; // Don't let getopt() print errors

    instance()->m_program_name = argv[0];

    // Handle flag arguments
    // `getopt(argc, argv, <expected flags>)` only parses flag arguments (like -b)
    // it returns an int that is one of the following:
    // =>  -1 if there are no more flag args
    // =>  the char of the expected flag, if found
    // =>  '?' if a flag arg was found but was not in the expected flags.
    // The returned value is as an int, so it will need to be converted to a char
    // before it can be checked properly.
    char c;
    while ((c = (char)getopt(argc, argv, "h")) != -1)
    {
        switch (c)
        {
            // The only acceptable flag argument is "-h" for the help.
        case 'h':
            print_help();
            return;
        case '?':
            std::string error_string = "Unknown option \"";
            error_string += ((char)optopt);
            error_string += "\".";
            throw std::runtime_error(error_string.c_str());
        }
    }

    int required_positional_args = 2; // this is true for 1, 2, and 4

    int remaining_args = argc - optind;

    if(remaining_args < required_positional_args)
    {
        throw std::runtime_error("Too few positional arguments.");
    }

    // Check the first positional argument.
    try
    {
        // Assume the first positional argument is in reference to the 
        // algorithm to be used. This converts directly to the AlgorithmSelection
        // enum if it is between 1 and 4, inclusive.
        int selection = std::stoi(argv[optind]);
        if( selection >= 1 && selection <= 5)
        {
            instance()->m_algorithm = (AlgorithmSelection) selection;
        }
        else
        {
            // Throw an exception if the algorithm selection number was not 1, 2, 3, or 4.
            std::string error_string = "The number used to select the algorithm must be between 1 and 5, inclusive. Got \"";
            error_string += argv[optind];
            error_string += "\".";
            throw std::runtime_error(error_string);
        }
        optind++;
        remaining_args--;
    }
    catch(const std::exception& e)
    {
        // If we caught an exception, it was because whatever was in the algorithm selection spot 
        // couldn't be read by std::stoi as an integer. Throw an exception of our own making.
        std::string error_string = "Expected a number for the first argument, got \"";
        error_string += argv[optind];
        error_string += "\".";
        throw std::runtime_error(error_string);
    }
    
    if (instance()->m_algorithm == AlgorithmSelection::COMPRESSED_SVD && remaining_args < 3)
    {
        throw std::runtime_error("Too few positional arguments to use the selected algorithm.");
    }

    // Assume that the positional arguments will be in the correct order
    // Assume that the given filepath is valid. Don't check it.
    for (int offset_optind = 0; optind + offset_optind < argc; offset_optind++)
    {
        remaining_args--;
        switch (instance()->m_algorithm)
        {
        case AlgorithmSelection::TO_BINARY:
        {
            instance()->m_text_pgm_filepath = argv[optind + offset_optind];
            std::string extension = fs::path(instance()->m_text_pgm_filepath).extension();
            std::string filename = fs::path(instance()->m_text_pgm_filepath).stem();
            filename.append("_b.");
            filename.append(extension);
            instance()->m_binary_pgm_filepath = fs::path(instance()->m_text_pgm_filepath).replace_filename(filename);
            return;
        }
        case AlgorithmSelection::FROM_BINARY:
        {
            instance()->m_binary_pgm_filepath = argv[optind + offset_optind];
            std::string extension = fs::path(instance()->m_binary_pgm_filepath).extension();
            std::string filename = fs::path(instance()->m_binary_pgm_filepath).stem();

            if(const auto pos = filename.rfind("_b") != std::string::npos)
            {
                filename.erase(pos, 2);
            }
            filename.append("_copy.");
            filename.append(extension);
            instance()->m_text_pgm_filepath = fs::path(instance()->m_binary_pgm_filepath).replace_filename(filename);
            return;
        }
        case AlgorithmSelection::COMPRESSED_SVD:
        {
            if(offset_optind == 0)
            {
                instance()->m_pgm_header_filepath = argv[optind + offset_optind];
            } else if (offset_optind == 1) {
                instance()->m_svd_matrices_filepath = argv[optind + offset_optind];
                std::string filename = fs::path(instance()->m_svd_matrices_filepath).stem();
                std::string extension = fs::path(instance()->m_svd_matrices_filepath).extension();
                filename.append("_b.");
                filename.append(extension);
                filename.append(".SVD");
                instance()->m_binary_pgm_filepath = fs::path(instance()->m_svd_matrices_filepath).replace_filename(filename);
            }
            else
            {
                try
                {
                    instance()->m_approximation_rank = std::stoi(argv[optind + offset_optind]);
                }
                catch(const std::exception& e)
                {
                    std::string error_string = "Expected a number for the approximation rank argument, got \"";
                    error_string += argv[optind];
                    error_string += "\".";
                    throw std::runtime_error(error_string);
                }
                return;
            }
            
            break;
        }
        case AlgorithmSelection::FROM_COMPRESSED_SVD:
        {
            instance()->m_binary_pgm_filepath = argv[optind + offset_optind];
            std::string filename = fs::path(instance()->m_binary_pgm_filepath).stem();
            instance()->m_text_pgm_filepath = fs::path(instance()->m_binary_pgm_filepath).replace_extension(); // Remove ".SVD"
            std::string extension = fs::path(instance()->m_binary_pgm_filepath).extension();
            filename.append("_k.");// TODO: Change k?
            filename.append(extension);
            instance()->m_text_pgm_filepath = fs::path(instance()->m_binary_pgm_filepath).replace_filename(filename);
            return;
        }
        case AlgorithmSelection::RANDOM_IMAGE:
        {
            instance()->m_text_pgm_filepath = argv[optind + offset_optind];
            return;
        }
        } 
    }
}

ProgramOptions::ProgramOptions()
    : m_algorithm(ProgramOptions::AlgorithmSelection::NONE),
      m_program_name(""),
      m_text_pgm_filepath(""),
      m_binary_pgm_filepath(""),
      m_pgm_header_filepath(""),
      m_svd_matrices_filepath(""),
      m_approximation_rank(0)
{}
