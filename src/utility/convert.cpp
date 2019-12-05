#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cstring>
#include <string.h>
#include "convert.hpp"

using namespace std;

void i4vec_to_ucvec ( int n, int *a, unsigned char *b )
{
  int i;

  for ( i = 0; i < n; i++ )
  {
    *b = ( unsigned char ) *a;
    a++;
    b++;
  }
  return;
}


void pgma_check_data ( int xsize, int ysize, int maxg, int *g )
{
  int i;
  int *index;
  int j;
  int k;

  if ( xsize <= 0 )
  {
    cerr<< "\n";
    cerr << "PGMA_CHECK_DATA: Error!\n";
    cerr << "  XSIZE <= 0.\n";
    cerr << "  XSIZE = " << xsize << "\n";
    exit ( 1 );
  }

  if ( ysize <= 0 )
  {
    cerr << "\n";
    cerr << "PGMA_CHECK_DATA: Error!\n";
    cerr << "  YSIZE <= 0.\n";
    cerr << "  YSIZE = " << ysize << "\n";
    exit ( 1 );
  }

  if ( g == NULL )
  {
    cerr << "\n";
    cerr << "PGMA_CHECK_DATA: Error!\n";
    cerr << "  Null pointer to g.\n";
    exit ( 1 );
  }

  index = g;

  for ( j = 0; j < ysize; j++ )
  {
    for ( i = 0; i < xsize; i++ )
    {
      if ( *index < 0 )
      {
        cerr << "\n";
        cerr << "PGMA_CHECK_DATA - Fatal error!\n";
        cerr << "  Negative data.\n";
        cerr << "  G(" << i << "," << j << ")=" << *index << "\n";
        exit ( 1 );
      }
      else if ( maxg < *index )
      {
        cerr << "\n";
        cerr << "PGMA_CHECK_DATA - Fatal error!\n";
        cerr << "  Data exceeds MAXG = " << maxg << "\n";
        cerr << "  G(" << i << "," << j << ")=" << *index << "\n";
        exit ( 1 );
      }
      index = index + 1;
    }
  }
  return;
}


void pgma_read ( string input_name, int *xsize, int *ysize, int *maxg,
  int **g )

{
  ifstream input;
  int numbytes;

  input.open ( input_name.c_str ( ) );

  if ( !input )
  {
    cerr << "\n";
    cerr << "PGMA_READ - Fatal error!\n";
    cerr << "  Cannot open the input file \"" << input_name << "\".\n";
    exit ( 1 );
  }

  pgma_read_header ( input, xsize, ysize, maxg );

  numbytes = (*xsize) * (*ysize) * sizeof ( int );

  *g = new int[numbytes];

  pgma_read_data ( input, *xsize, *ysize, *g );

  input.close ( );

  return;
}


void pgma_read_data ( ifstream &input, int xsize, int ysize, int *g )
{
  int i;
  int j;

  for ( j = 0; j < ysize; j++ )
  {
    for ( i = 0; i < xsize; i++ )
    {
      input >> *g;
      if ( input.eof ( ) )
      {
        exit ( 1 );
      }
      g = g + 1;
    }
  }

  return;
}


void pgma_read_header ( ifstream &input, int *xsize, int *ysize, int *maxg )
{
  int count;
  string line;
  string rest;
  int step;
  int width;
  string word;

  step = 0;

  while ( 1 )
  {
    getline ( input, line );

    if ( input.eof ( ) )
    {
      cerr << "\n";
      cerr << "PGMA_READ_HEADER - Fatal error!\n";
      cerr << "  End of file.\n";
      exit ( 1 );
    }

    if ( line[0] == '#' )
    {
      continue;
    }

    if ( step == 0 )
    {
      s_word_extract_first ( line, word, rest );

      if ( s_len_trim ( word ) == 0 )
      {
        continue;
      }
      line = rest;

      if ( ( word[0] != 'P' && word[0] != 'p' ) ||
             word[1] != '2' )
      {
        cerr << "\n";
        cerr << "PGMA_READ_HEADER - Fatal error.\n";
        cerr << "  Bad magic number = \"" << word << "\".\n";
        exit ( 1 );
      }
      step = 1;
    }

    if ( step == 1 )
    {
      s_word_extract_first ( line, word, rest );

      if ( s_len_trim ( word ) == 0 )
      {
        continue;
      }
      *xsize = atoi ( word.c_str ( ) );
      line = rest;
      step = 2;
    }

    if ( step == 2 )
    {
      s_word_extract_first ( line, word, rest );

      if ( s_len_trim ( word ) == 0 )
      {
        continue;
      }
      *ysize = atoi ( word.c_str ( ) );
      line = rest;
      step = 3;
    }

    if ( step == 3 )
    {
      s_word_extract_first ( line, word, rest );

      if ( s_len_trim ( word ) == 0 )
      {
        continue;
      }
      *maxg = atoi ( word.c_str ( ) );
      break;
    }

  }

  return;
}


bool pgma_to_pgmb ( char *file_in_name, char *file_out_name )
{
  int *g;
  unsigned char *g2;
  bool error = false;
  int maxg;
  int xsize;
  int ysize;

  pgma_read ( file_in_name, &xsize, &ysize, &maxg, &g );

  if ( error )
  {
    cout << "\n";
    cout << "PGMA_TO_PGMB: Fatal error!\n";
    cout << "  PGMA_READ failed.\n";
    return true;
  }

  pgma_check_data ( xsize, ysize, maxg, g );

  g2 = new unsigned char [ xsize * ysize ];
  i4vec_to_ucvec ( xsize * ysize, g, g2 );
  delete [] g;

  error = pgmb_write ( file_out_name, xsize, ysize, g2, maxg );

  delete [] g2;

  if ( error )
  {
    cout << "\n";
    cout << "PGMA_TO_PGMB: Fatal error!\n";
    cout << "  PGMB_WRITE failed.\n";
    return true;
  }

  return false;
}

bool pgmb_write ( string output_name, int xsize, int ysize, unsigned char *g, int maxgt )
{
  bool error;
  ofstream output;
  int i;
  unsigned char *indexg;
  int j;
  unsigned char maxg;

  maxg = maxgt;
  indexg = g;

  for ( i = 0; i < xsize; i++ )
  {
    for ( j = 0; j < ysize; j++ )
    {
      /*if ( maxg < *indexg )
      {
        maxg = *indexg;
      }*/
      indexg = indexg + 1;
    }
  }

  output.open ( output_name.c_str ( ), ios::binary );

  if ( !output )
  {
    cout << "\n";
    cout << "PGMB_WRITE: Fatal error!\n";
    cout << "  Cannot open the output file " << output_name << "\n";
    return true;
  }

  error = pgmb_write_header ( output, xsize, ysize, maxg );

  if ( error )
  {
    cout << "\n";
    cout << "PGMB_WRITE: Fatal error!\n";
    cout << "  PGMB_WRITE_HEADER failed.\n";
    return true;
  }

  error = pgmb_write_data ( output, xsize, ysize, g );

  if ( error )
  {
    cout << "\n";
    cout << "PGMB_WRITE: Fatal error!\n";
    cout << "  PGMB_WRITE_DATA failed.\n";
    return true;
  }

  output.close ( );

  return false;
}


bool pgmb_write_data ( ofstream &output, int xsize, int ysize, unsigned char *g )
{
  int i;
  unsigned char *indexg;
  int j;

  indexg = g;

  for ( j = 0; j < ysize; j++ )
  {
    for ( i = 0; i < xsize; i++ )
    {
      output << *indexg;
      indexg = indexg + 1;
    }
  }

  return false;
}


bool pgmb_write_header ( ofstream &output, int xsize, int ysize, unsigned char maxg )
{
  output << "P5" << " "
           << xsize << " "
           << ysize << " "
           << ( int ) maxg << "\n";

  return false;
}


void s_word_extract_first ( string s, string &s1, string &s2 )
{
  int i;
  int mode;
  int s_len;

  s_len = s.length ( );
  s1 = "";
  s2 = "";
  mode = 1;

  for ( i = 0; i < s_len; i++ )
  {
    if ( mode == 1 )
    {
      if ( s[i] != ' ' )
      {
         mode = 2;
      }
    }
    else if ( mode == 2 )
    {
      if ( s[i] == ' ' )
      {
        mode = 3;
      }
    }
    else if ( mode == 3 )
    {
      if ( s[i] != ' ' )
      {
        mode = 4;
      }
    }
    if ( mode == 2 )
    {
      s1 = s1 + s[i];
    }
    else if ( mode == 4 )
    {
      s2 = s2 + s[i];
    }
  }

  return;
}


void timestamp ( )
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  size_t len;
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  len = strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  cout << time_buffer << "\n";

  return;
# undef TIME_SIZE
}


int s_len_trim ( string s )
{
  int n;

  n = s.length ( );

  while ( 0 < n )
  {
    if ( s[n-1] != ' ' )
    {
      return n;
    }
    n = n - 1;
  }

  return n;
}

//---------------------------------------------------------------------------------

char ch_cap ( char ch )
{
  if ( 97 <= ch && ch <= 122 )
  {
    ch = ch - 32;
  }

  return ch;
}


void pgma_write ( string output_name, int xsize, int ysize, int *g, int maxgt )
{
  ofstream output;
  int i;
  int *indexg;
  int j;
  int maxg;

  output.open ( output_name.c_str ( ) );

  if ( !output )
  {
    cerr << "\n";
    cerr << "PGMA_WRITE - Fatal error!\n";
    cerr << "  Cannot open the output file \"" << output_name << "\".\n";
    exit ( 1 );
  }

  maxg = maxgt;
  indexg = g;

  for ( j = 0; j < ysize; j++ )
  {
    for ( i = 0; i < xsize; i++ )
    {
      /*if ( maxg < *indexg )
      {
        maxg = *indexg;
      }*/
      indexg = indexg + 1;

    }
  }

  pgma_write_header ( output, output_name, xsize, ysize, maxg );

  pgma_write_data ( output, xsize, ysize, g );

  output.close ( );

  return;
}

void pgma_write_data ( ofstream &output, int xsize, int ysize, int *g )
{
  int i;
  int *indexg;
  int j;
  int numval;

  indexg = g;
  numval = 0;

  for ( j = 0; j < ysize; j++ )
  {
    for ( i = 0; i < xsize; i++ )
    {
      output << *indexg;
      numval = numval + 1;
      indexg = indexg + 1;

      if ( numval % 12 == 0 || i == xsize - 1 || numval == xsize * ysize )
      {
        output << "\n";
      }
      else
      {
        output << " ";
      }

    }
  }
  return;
}

void pgma_write_header ( ofstream &output, string output_name, int xsize,int ysize, int maxg )
{
  output << "P2\n";
  output << "# " << output_name << " created by PGMA_IO::PGMA_WRITE.\n";
  output << xsize << "  " << ysize << "\n";
  output << maxg << "\n";

  return;
}


bool pgmb_check_data ( int xsize, int ysize, unsigned char maxg, unsigned char *g )
{
  int i;
  unsigned char *index;
  int j;
  int k;

  if ( xsize <= 0 )
  {
    cout << "\n";
    cout << "PGMB_CHECK_DATA: Error!\n";
    cout << "  xsize <= 0.\n";
    cout << "  xsize = " << xsize << "\n";
    return true;
  }

  if ( ysize <= 0 )
  {
    cout << "\n";
    cout << "PGMB_CHECK_DATA: Error!\n";
    cout << "  ysize <= 0.\n";
    cout << "  ysize = " << ysize << "\n";
    return true;
  }

  if ( g == NULL )
  {
    cout << "\n";
    cout << "PGMB_CHECK_DATA: Error!\n";
    cout << "  Null pointer to g.\n";
    return true;
  }

  index = g;

  for ( j = 0; j < ysize; j++ )
  {
    for ( i = 0; i < xsize; i++ )
    {
      if ( maxg < *index )
      {
        cout << "\n";
        cout << "PGMB_CHECK_DATA - Fatal error!\n";
        cout << "  Data exceeds MAXG = " << ( int ) maxg << "\n";
        cout << "  G(" << i << "," << j << ")=" << ( int ) (*index) << "\n";
        return true;
      }

      index = index + 1;
    }
  }

  return false;
}


bool pgmb_read ( string input_name, int *xsize, int *ysize, unsigned char *maxg, unsigned char **g )
{
  bool error;
  ifstream input;
  int numbytes;

  input.open ( input_name.c_str ( ), ios::binary );

  if ( !input )
  {
    cout << "\n";
    cout << "PGMB_READ: Fatal error!\n";
    cout << "  Cannot open the input file " << input_name << "\n";
    return true;
  }

  error = pgmb_read_header ( input, xsize, ysize, maxg );

  if ( error )
  {
    cout << "\n";
    cout << "PGMB_READ: Fatal error!\n";
    cout << "  PGMB_READ_HEADER failed.\n";
    return true;
  }

  *g = new unsigned char [ (*xsize) * (*ysize) ];

  error = pgmb_read_data ( input, *xsize, *ysize, *g );

  if ( error )
  {
    cout << "\n";
    cout << "PGMB_READ: Fatal error!\n";
    cout << "  PGMB_READ_DATA failed.\n";
    return true;
  }

  input.close ( );

  return false;
}


bool pgmb_read_data ( ifstream &input, int xsize, int ysize, unsigned char *g )
{
  char c;
  bool error;
  int i;
  unsigned char *indexg;
  int j;

  indexg = g;

  for ( j = 0; j < ysize; j++ )
  {
    for ( i = 0; i < xsize; i++ )
    {
      input.read ( &c, 1 );
      *indexg = ( unsigned char ) c;
      indexg = indexg + 1;
      error = input.eof();
      if ( error )
      {
        cout << "\n";
        cout << "PGMB_READ_DATA - Fatal error!\n";
        cout << "  End of file reading pixel ("
          << i << ", " << j <<") \n";
        return true;
      }
    }
  }
  return false;
}


bool pgmb_read_header ( ifstream &input, int *xsize, int *ysize, unsigned char *maxg )
{
  int count;
  int fred;
  string line;
  int maxg2;
  string rest;
  int step;
  int width;
  string word;

  step = 0;

  while ( 1 )
  {
    getline ( input, line );

    if ( input.eof ( ) )
    {
      cout << "\n";
      cout << "PGMB_READ_HEADER - Fatal error!\n";
      cout << "  End of file.\n";
      return true;
    }

    if ( line[0] == '#' )
    {
      continue;
    }

    if ( step == 0 )
    {
      s_word_extract_first ( line, word, rest );

      if ( s_len_trim ( word ) <= 0 )
      {
        continue;
      }

      if ( !s_eqi ( word, "P5" ) )
      {
        cout << "\n";
        cout << "PGMB_READ_HEADER - Fatal error.\n";
        cout << "  Bad magic number = \"" << word << "\".\n";
        return true;
      }
      line = rest;
      step = 1;
    }

    if ( step == 1 )
    {
      s_word_extract_first ( line, word, rest );

      if ( s_len_trim ( word ) <= 0 )
      {
        continue;
      }
      *xsize = atoi ( word.c_str ( ) );
      line = rest;
      step = 2;
    }

    if ( step == 2 )
    {
      s_word_extract_first ( line, word, rest );

      if ( s_len_trim ( word ) <= 0 )
      {
        continue;
      }
      *ysize = atoi ( word.c_str ( ) );
      line = rest;
      step = 3;
    }

    if ( step == 3 )
    {
      s_word_extract_first ( line, word, rest );

      if ( s_len_trim ( word ) <= 0 )
      {
        continue;
      }
      fred = atoi ( word.c_str ( ) );
      *maxg = ( unsigned char ) fred;
      line = rest;
      break;
    }
  }

  return false;
}


bool pgmb_to_pgma ( char *file_in_name, char *file_out_name )
{
  bool error;
  unsigned char *g;
  int *g2;
  unsigned char maxg;
  int xsize;
  int ysize;

  error = pgmb_read ( file_in_name, &xsize, &ysize, &maxg, &g );

  if ( error )
  {
    cout << "\n";
    cout << "PGMB_TO_PGMA: Fatal error!\n";
    cout << "  PGMB_READ failed.\n";
    return true;
  }

  error = pgmb_check_data ( xsize, ysize, maxg, g );

  if ( error )
  {
    cout << "\n";
    cout << "PGMB_TO_PGMA: Fatal error!\n";
    cout << "  PGMB_CHECK_DATA reports bad data from the file.\n";

    delete [] g;
    return true;
  }

  g2 = new int [ xsize *  ysize ];
  ucvec_to_i4vec ( xsize * ysize, g, g2 );
  delete [] g;

  pgma_write ( file_out_name, xsize, ysize, g2, maxg );

  delete [] g2;

  if ( error )
  {
    cout << "\n";
    cout << "PGMB_TO_PGMA: Fatal error!\n";
    cout << "  PGMA_WRITE failed.\n";
    return true;
  }

  return false;
}


bool s_eqi ( string s1, string s2 )
{
  int i;
  int nchar;
  int s1_length;
  int s2_length;

  s1_length = s1.length ( );
  s2_length = s2.length ( );

  if ( s1_length < s2_length )
  {
    nchar = s1_length;
  }
  else
  {
    nchar = s2_length;
  }

  for ( i = 0; i < nchar; i++ )
  {

    if ( ch_cap ( s1[i] ) != ch_cap ( s2[i] ) )
    {
      return false;
    }
  }

  if ( nchar < s1_length )
  {
    for ( i = nchar; i < s1_length; i++ )
    {
      if ( s1[i] != ' ' )
      {
        return false;
      }
    }
  }
  else if ( nchar < s2_length )
  {
    for ( i = nchar; i < s2_length; i++ )
    {
      if ( s2[i] != ' ' )
      {
        return false;
      }
    }
  }

  return true;
}


void ucvec_to_i4vec ( int n, unsigned char *a, int *b )
{
  int i;

  for ( i = 0; i < n; i++ )
  {
    *b = ( int ) *a;
    a++;
    b++;
  }

  return;
}
