#include "program_options.hpp"

#include <unistd.h>
#include <climits>
#include <getopt.h>
#include <iostream>
#include <sstream>

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
    std::cout << "      Team Member 1    <TM001@zips.uakron.edu>" << std::endl;
    std::cout << "      Team Member 2    <TM0002@zips.uakron.edu>" << std::endl;
    std::cout << "       Edwin Sarver    <els40@zips.uakron.edu>" << std::endl;

}

void ProgramOptions::parse(int argc, char** argv)
{
    //TODO UPDATE THIS!
    int bfs_flag = 0;
    int ff_flag = 0;
    int circ_flag = 0;

    optind = 1; // reset getopt()
    opterr = 0; // Don't let getopt() print errors

    instance()->m_program_name = argv[0];

    // Handle flag arguments
    // `getopt(argc, argv, <expected flags>)` only parses flag arguments (like -b)
    // it returns and int that is one of the following:
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
        case 'h':
            print_help();
            return;
        case '?':
            std::string error_string = "Unknown option \"";
            error_string += ((char)optopt);
            error_string += "\".";
            throw error_string;
        }
    }

    // Only allow one algorithm to be chosen:

    // handle positional options
    // int required_positional_args = 3; // bfs
    // if (ff_flag || circ_flag)
    // {
    //     required_positional_args = 1;
    // }

    // int remaining_args = argc - optind;

    // if(remaining_args < required_positional_args)
    // {
    //     throw "Too few positional arguments for selected algorithm.";
    // }

    // // Assume that the positional arguments will be in the correct order
    // // Assume that the given filepath is valid. Don't check it.
    // for (int offset_optind = 0; optind + offset_optind < argc; offset_optind++)
    // {
    //     remaining_args--;
    //     switch (offset_optind)
    //     {
    //     case 0:
    //         instance()->m_graph_filepath = argv[offset_optind + optind];
    //         break;
    //     case 1:
    //         try {
    //             instance()->m_source_node = std::stoi(argv[offset_optind + optind]);
    //         } catch (const std::invalid_argument&) {
    //             throw "Could not parse source-node argument.";
    //         }
    //         break;
    //     case 2:
    //         try {
    //             instance()->m_target_node = std::stoi(argv[offset_optind + optind]);
    //         } catch (const std::invalid_argument&) {
    //             throw "Could not parse target-node argument.";
    //         }
    //         break;
    //     }

    //     if (remaining_args <= 0)
    //     {
    //         break;
    //     }
    // }
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
