#include <fstream>
#include <getopt.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <string.h>

#include "convert.hpp"
#include "program_options.hpp"

void random_pgm(string filename, int xsize, int ysize)
{
    ofstream newpgm;
    int num;
    filename = filename + ".pgm";
    newpgm.open(filename);
    pgma_write_header(newpgm,filename,xsize,ysize,255);
    for(int i=0;i<xsize;i++)
    {
        for(int z=0;z<ysize;z++)
        {
            num = rand()%255+1;
            newpgm << num << " ";
        }
        newpgm << "\n";
    }
}

int main(int argc, char **argv)
{
  try {
    ProgramOptions::parse(argc, argv);

    switch(ProgramOptions::selected_algorithm())
    {
    case ProgramOptions::AlgorithmSelection::TO_BINARY:
    {
        //std::string input_file = ProgramOptions::text_pgm_filepath();
        //std::string output_file = ProgramOptions::binary_pgm_filepath();
        //std::cout << input_file << " " << output_file;
        // TODO: ASCII to Binary implementation here...
        bool error;
        char file_in_name[80];
        char file_out_name[80];
        int length = strlen(argv[2]);
        strcpy(file_in_name, argv[2]);
        strncpy (file_out_name,file_in_name,length-4);
        file_out_name[length-4] = '\0';
        std::cout << file_out_name << std::endl;
        strcat (file_out_name,"_b.pgm");
        std::cout << file_out_name;
        error = pgma_to_pgmb(file_in_name,file_out_name);
        return 0;
    }
    case ProgramOptions::AlgorithmSelection::FROM_BINARY:
    {
        //std::string input_file = ProgramOptions::binary_pgm_filepath();
        //std::string output_file = ProgramOptions::text_pgm_filepath();
        // TODO: Binary to ASCII implementation here...
        bool error;
        char file_in_name[80];
        char file_out_name[80];
        int length = strlen(argv[2]);
        strcpy(file_in_name, argv[2]);
        strncpy (file_out_name,file_in_name,length-4);
        file_out_name[length-4] = '\0';
        strcat (file_out_name,"_copy.pgm");
        //cout << file_out_name;
        error = pgmb_to_pgma ( file_in_name, file_out_name );
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
    case ProgramOptions::AlgorithmSelection::RANDOM_IMAGE:
    {
        std::string output_file = ProgramOptions::text_pgm_filepath();
        int xsize;
        int ysize;
        std::cout << "Please input the xsize : ";
        std::cin >> xsize;
        std::cout << "Please input the ysize : ";
        std::cin >> ysize;
        //cout << xsize << " " << ysize;
        random_pgm(output_file,xsize,ysize);
        std::cout << "pass";
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

<<<<<<< HEAD
=======
void random_pgm(string filename, int xsize, int ysize)
{
    ofstream newpgm;
    int num;
    filename = filename + ".pgm";
    newpgm.open(filename);
    pgma_write_header(newpgm,filename,xsize,ysize,255);
    for(int i=0;i<xsize;i++)
    {
        for(int z=0;z<ysize;z++)
        {
            num = rand()%255+1;
            newpgm << num << " ";
        }
        newpgm << "\n";
    }
}
>>>>>>> 03a96ec93dc514c2c4d3c299214bda56a0f0cf21
