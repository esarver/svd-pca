#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cstring>
#include <string.h>

using namespace std;

void i4vec_to_ucvec ( int n, int *a, unsigned char *b );
void pgma_check_data ( int xsize, int ysize, int maxg, int *g );
void pgma_read ( string input_name, int *xsize, int *ysize, int *maxg, int **g );
void pgma_read_data ( ifstream &input, int xsize, int ysize, int *g );
void pgma_read_header ( ifstream &input, int *xsize, int *ysize, int *maxg );
bool pgma_to_pgmb ( char *file_in_name, char *file_out_name );
bool pgmb_write ( string output_name, int xsize, int ysize, unsigned char *g, int maxgt ) ;
bool pgmb_write_data ( ofstream &output, int xsize, int ysize, unsigned char *g );
bool pgmb_write_header ( ofstream &output, int xsize, int ysize, unsigned char maxg );
int s_len_trim ( string s );
void s_word_extract_first ( string s, string &s1, string &s2 );
void timestamp ( );

char ch_cap ( char ch );
void pgma_write ( string output_name, int xsize, int ysize, int *g, int maxgt );
void pgma_write_data ( ofstream &output, int xsize, int ysize, int *g );
void pgma_write_header ( ofstream &output, string output_name, int xsize, int ysize, int maxg );
bool pgmb_check_data ( int xsize, int ysize, unsigned char maxg, unsigned char *g );
bool pgmb_read ( string input_name, int *xsize, int *ysize, unsigned char *maxg, unsigned char **g );
bool pgmb_read_data ( ifstream &input, int xsize, int ysize, unsigned char *g );
bool pgmb_read_header ( ifstream &input, int *xsize, int *ysize, unsigned char *maxg );
bool pgmb_to_pgma ( char *file_in_name, char *file_out_name );
bool s_eqi ( string s1, string s2 );
void ucvec_to_i4vec ( int n, unsigned char *a, int *b );
