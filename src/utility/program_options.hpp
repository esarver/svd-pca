#pragma once
#include <string>

/**
 * @brief The ProgramOptions class is a singleton class with a
 * fully static interface. It contains all the information the user
 * provided on the command-line.
 */
class ProgramOptions
{
public:

    /**
     * @brief The AlgorithmSelection enum defines the 3 different supported
     * Algorithms used in this program.
     *
     *            BFS: Breadth-First Search
     * FORD_FULKERSON: The Ford-Fulkerson algorithm implemented using the BFS
     *    CIRCULATION: The solution for the circulation problem
     */
    enum AlgorithmSelection
    {
        NONE = 0,
        TO_BINARY = 1,
        FROM_BINARY = 2,
        COMPRESSED_SVD = 3,
        FROM_COMPRESSED_SVD = 4,
        RANDOM_IMAGE = 5
    };

    /**
     * @brief Clears the current ProgramOptions instance
     *
     * There isn't much normal use for this method besides
     * in testing.
     */
    static void clear();

    /**
     * @brief Get the provided filepath of the graph text-file
     * @return The provided filepath string
     */
    static const std::string graph_filepath();

    /**
     * @brief Get the singleton instance of ProgramOptions
     *
     * Check to see if an instance already exists.
     * If it does return that.
     * Otherwise, instantiate an instance and return that one.
     *
     * @return The current singleton instance of ProgramOptions
     *
     */
    static ProgramOptions* instance();

    /**
     * @brief Parse the input options sent on the command line.
     *
     * Perform some basic error-checking.
     * 
     * Example inputs:
     * `<program_name> -b file/path/name.ext 0 5`
     * `<program_name> -f file/path/name.ext`
     * `<program_name> -c file/path/name.ext`
     *
     * @throws std::string with the error-text.
     *
     * @param argc - The argc that is sent down from the system
     * @param argv - The argv that is sent down from the system
     */
    static void parse(int argc, char** argv);

    /**
     * @brief Prints the help message.
     */
    static void print_help();

    /**
     * @brief Get the name of the program as it was run by the user
     * @return The name of the program as it was run by the user
     */
    static const std::string& program_name();

    /**
     * @brief Get which algorithm was selected
     * @return The enum the IDs the selected algorithm
     */
    static AlgorithmSelection selected_algorithm();

    /**
     * @brief Get the filepath given for the ASCII pgm
     * file
     * 
     * @return The filepath string for the ASCII pgm file 
     */
    static const std::string& text_pgm_filepath();

    /**
     * @brief Get the filepath given for the binary pgm
     * file
     * 
     * @return The filepath string for the binary pgm file 
     */
    static const std::string& binary_pgm_filepath();
    
    /**
     * @brief Get the filepath given for the pgm header
     * file
     * 
     * @return The filepath string for the pgm header file 
     */
    static const std::string& pgm_header_filepath();

    /**
     * @brief Get the filepath given for the SVD matrices
     * file
     * 
     * @return The filepath string for the SVD matrices file 
     */
    static const std::string& svd_matrices_filepath();

    /**
     * @brief Get the approximation rank
     * 
     * @return the integer given for the approximation rank
     */
    static int approximation_rank();


private:
    /**
     * @brief The hidden constructor for the ProgramOptions singleton.
     */
    ProgramOptions();
    
    AlgorithmSelection m_algorithm;
    std::string m_program_name;
    std::string m_text_pgm_filepath;
    std::string m_binary_pgm_filepath;
    std::string m_pgm_header_filepath;
    std::string m_svd_matrices_filepath;
    int m_approximation_rank;

    static ProgramOptions* s_instance;

};
