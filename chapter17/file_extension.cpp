// Find files that have ".cc", ".Cc", ".cC", "CC", "cpp", "cPp".... extension
#include <iostream>
#include <regex>
#include <fstream>

using namespace std;

int main() {
  // 1 or more digits; a dot; one of the extensions
  // with flag "ignore-case" (icase)
  regex r("[[:alnum:]]+\\.(cpp|cxx|cc)$", regex::icase);
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