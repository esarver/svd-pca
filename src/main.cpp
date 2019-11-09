#include <fstream>
#include <getopt.h>
#include <iostream>
#include <string>
#include <unistd.h>

#include "program_options.hpp"

int main(int argc, char **argv)
{
  try {
    ProgramOptions::parse(argc, argv);

    switch(ProgramOptions::selected_algorithm())
    {
    case ProgramOptions::AlgorithmSelection::TO_BINARY:
    {
        std::string input_file = ProgramOptions::text_pgm_filepath();
        std::string output_file = ProgramOptions::binary_pgm_filepath();
        // TODO: ASCII to Binary implementation here...
        return 0;
    }
    case ProgramOptions::AlgorithmSelection::FROM_BINARY:
    {
        std::string input_file = ProgramOptions::binary_pgm_filepath();
        std::string output_file = ProgramOptions::text_pgm_filepath();
        // TODO: Binary to ASCII implementation here...
        return 0;
    }
    case ProgramOptions::AlgorithmSelection::COMPRESSED_SVD:
    {
        std::string input_file = ProgramOptions::svd_matrices_filepath();
        std::string header_file = ProgramOptions::pgm_header_filepath();
        std::string output_file = ProgramOptions::binary_pgm_filepath();
        // TODO: SVD implementation here...
        return 0;
    }
    case ProgramOptions::AlgorithmSelection::FROM_COMPRESSED_SVD:
    {
        std::string input_file = ProgramOptions::binary_pgm_filepath();
        std::string output_file = ProgramOptions::text_pgm_filepath();
        // TODO: (SVD)^-1 implementation here...
        return 0;
    }
    default:
        throw std::runtime_error("Unknown algorithm type.");
    }

  }
  catch (const std::runtime_error &e) { // if the user mis-entered anything, just print the help.
    std::cerr << "ERROR: " << e.what() << std::endl;
    ProgramOptions::print_help();
  }
}
