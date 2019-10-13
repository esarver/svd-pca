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

    // std::ifstream in_file(ProgramOptions::graph_filepath());

  }
  catch (const std::runtime_error &e) { // if the user mis-entered anything, just print the help.
    std::cerr << "ERROR: " << e.what() << std::endl;
    ProgramOptions::print_help();
  }
}
