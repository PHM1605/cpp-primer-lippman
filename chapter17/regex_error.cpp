// Find files that have ".cc", ".Cc", ".cC", "CC", "cpp", "cPp".... extension
// try <regex_error>
#include <iostream>
#include <regex>
#include <fstream>

using namespace std;

int main() {
  regex r; 
  try {
    // NOTE: we purposedly remove a ']'
    regex r("[[:alnum:]+\\.(cpp|cxx|cc)$", regex::icase);
  } catch(regex_error e) {
    cout << e.what() << "\ncode: " << e.code() << endl;
    return 1; 
  }
  
  smatch results;

  ifstream infile("file_extension_input.txt");
  if (!infile) {
    cerr << "Error: cannot open file_extension_input.txt\n";
    return 1;
  }
  
  string filename;
  while (getline(infile, filename)) {
    if (regex_search(filename, results, r)) {
      cout << results.str() << endl;
    }
  }

  return 0;
}