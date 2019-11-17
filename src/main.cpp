#include <fstream>
#include <getopt.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <string.h>
#include <regex>
#include <ctime>

#include "convert.hpp"
#include "program_options.hpp"
#include "svd.hpp"

void random_pgm(string filename, int xsize, int ysize, int maxlimit, int minlimit)
{
    srand(time(NULL));
    ofstream newpgm;
    int num;
    filename = filename + ".pgm";
    newpgm.open(filename);
    pgma_write_header(newpgm,filename,xsize,ysize,255);
    for(int i=0;i<xsize;i++)
    {
        for(int z=0;z<ysize;z++)
        {
            num = rand()%(maxlimit-minlimit)+1+minlimit;
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
        int rank = ProgramOptions::approximation_rank();
        // TODO: SVD implementation here...

        std::ifstream header(header_file);
        std::ifstream pgm(input_file);
        SVD::decomp decomposition = SVD::pgmSvdToHalfStream(header, pgm, rank);
        header.close();
        pgm.close();

        SVD::writePgmAsSvd(output_file, decomposition);

        std::cout << "Wrote compressed image to \"" << output_file << "\"" << std::endl;
        return 0;
    }
    case ProgramOptions::AlgorithmSelection::FROM_COMPRESSED_SVD:
    {
        std::string input_file = ProgramOptions::binary_pgm_filepath();
        std::string output_file = ProgramOptions::text_pgm_filepath();
        // TODO: (SVD)^-1 implementation here...

        auto [pgm, rank] = SVD::svdToPGMString(input_file);

        output_file = std::regex_replace(output_file, std::regex("_k"), "_" + std::to_string(rank));
        std::ofstream output(output_file);
        output << pgm;

        output.close();
        std::cout << "Wrote decompressed image to \"" << output_file << "\"" << std::endl;
        return 0;
    }
    case ProgramOptions::AlgorithmSelection::RANDOM_IMAGE:
    {
        std::string output_file = ProgramOptions::text_pgm_filepath();
        bool check = false;
        string filename;
        int maxn = 255,minn = 0;
        //std::cout << argc;
        if(argc == 7 && atoi(argv[5]) >= 0 && atoi(argv[5]) <= 255 && atoi(argv[6]) >= 0 && atoi(argv[6]) <= 255 && atoi(argv[6]) < atoi(argv[5]))
        {
            maxn = atoi(argv[5]);
            minn = atoi(argv[6]);
            //std::cout << "limit";
        }
        int xsize = atoi(argv[3]);
        int ysize = atoi(argv[4]);
        random_pgm(output_file,xsize,ysize,maxn,minn);
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
