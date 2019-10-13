#include "gtest/gtest.h"

#include <climits>
#include "program_options.hpp"

TEST (ProgramOptionsParser, CanParseCorrectInputForAlgo1)
{
    // Clear the ProgramOptions singleton or else crazy things happen...
    ProgramOptions::clear();

    //set up the mock inputs
    char* moc_argv[] = {
        "program_name", // program name at index 0
        "1", // Algorithm selection
        "image.pgm", // Filename
        NULL
    };

    int moc_argc = sizeof(moc_argv) / sizeof(char*) - 1;

    // parse it
    ProgramOptions::parse(moc_argc, moc_argv);

    // check it
    EXPECT_EQ(ProgramOptions::program_name(), "program_name");
    EXPECT_EQ(ProgramOptions::selected_algorithm(),
              ProgramOptions::AlgorithmSelection::TO_BINARY);
    EXPECT_EQ(ProgramOptions::text_pgm_filepath(), "image.pgm");
}

TEST (ProgramOptionsParser, CanParseCorrectInputForAlgo2)
{
    // Clear the ProgramOptions singleton or else crazy things happen...
    ProgramOptions::clear();

    //set up the mock inputs
    char* moc_argv[] = {
        "program_name", // program name at index 0
        "2", // Algorithm selection
        "image.pgm", // Filename
        NULL
    };

    int moc_argc = sizeof(moc_argv) / sizeof(char*) - 1;

    // parse it
    ProgramOptions::parse(moc_argc, moc_argv);

    // check it
    EXPECT_EQ(ProgramOptions::program_name(), "program_name");
    EXPECT_EQ(ProgramOptions::selected_algorithm(),
              ProgramOptions::AlgorithmSelection::FROM_BINARY);
    EXPECT_EQ(ProgramOptions::binary_pgm_filepath(), "image.pgm");
}

TEST (ProgramOptionsParser, CanParseCorrectInputForAlgo3)
{
    // Clear the ProgramOptions singleton or else crazy things happen...
    ProgramOptions::clear();

    //set up the mock inputs
    char* moc_argv[] = {
        "program_name", // program name at index 0
        "3", // Algorithm selection
        "header.txt", // Filename
        "SVD.txt", // Filename
        "3",
        NULL
    };

    int moc_argc = sizeof(moc_argv) / sizeof(char*) - 1;

    // parse it
    ProgramOptions::parse(moc_argc, moc_argv);

    // check it
    EXPECT_EQ(ProgramOptions::program_name(), "program_name");
    EXPECT_EQ(ProgramOptions::selected_algorithm(),
              ProgramOptions::AlgorithmSelection::COMPRESSED_SVD);
    EXPECT_EQ(ProgramOptions::pgm_header_filepath(), "header.txt");
    EXPECT_EQ(ProgramOptions::svd_matrices_filepath(), "SVD.txt");
    EXPECT_EQ(ProgramOptions::approximation_rank(), 3);
}

TEST (ProgramOptionsParser, CanParseCorrectInputForAlgo4)
{
    // Clear the ProgramOptions singleton or else crazy things happen...
    ProgramOptions::clear();

    //set up the mock inputs
    char* moc_argv[] = {
        "program_name", // program name at index 0
        "1", // Algorithm selection
        "image.pgm", // Filename
        NULL
    };

    int moc_argc = sizeof(moc_argv) / sizeof(char*) - 1;

    // parse it
    ProgramOptions::parse(moc_argc, moc_argv);

    // check it
    EXPECT_EQ(ProgramOptions::program_name(), "program_name");
    EXPECT_EQ(ProgramOptions::selected_algorithm(),
              ProgramOptions::AlgorithmSelection::FROM_COMPRESSED_SVD);
    EXPECT_EQ(ProgramOptions::binary_pgm_filepath(), "image.pgm");
}