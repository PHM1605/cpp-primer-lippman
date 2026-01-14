// Read exercise10_33_input.txt; which holds integers
// -> exercise10_33_output_1.txt: holds odd values separated by " "
// -> exercise10_33_output_1.txt: holds even values separated by "\n"
// ==> run by "./a.out exercise10_33_input.txt exercise10_33_output_1.txt exercise10_33_output_2.txt"
#include <iostream>
#include <fstream>
#include <iterator>

using namespace std;

int main(int argc, char* argv[]) {
  ifstream in(argv[1]);
  ofstream out_odd(argv[2]);
  ofstream out_even(argv[3]);

  istream_iterator<int> iter_in(in), eof;
  ostream_iterator<int> iter_out_odd(out_odd, " ");
  ostream_iterator<int> iter_out_even(out_even, "\n");

  for (; iter_in!=eof; iter_in++) {
    if (*iter_in % 2)
      *iter_out_odd = *iter_in;
    else 
      *iter_out_even = *iter_in;
  }

  return 0;
}