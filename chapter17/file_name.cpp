// Print only file name (no extension) using <subexpression>
#include <iostream>
#include <regex>
#include <fstream>

using namespace std;

int main() {
  regex r("([[:alnum:]]+)\\.(cpp|cxx|cc)$", regex::icase);
  ifstream infile("file_extension_input.txt");
  if (!infile) {
    cerr << "Error: cannot open file_extension_input.txt\n";
    return 1;
  }

  string filename;
  smatch results;
  while(getline(infile, filename)) {
    if (regex_search(filename, results, r)) {
      // print the 1st <subexpression> i.e. file name
      cout << results.str(1) << endl; 
    }
  }

  return 0;
}