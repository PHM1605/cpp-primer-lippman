// Write a zip-code program
// Zipcode format: xxxxx-yyyy with the latter 4 digits optional
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

bool valid(const smatch& m) {
  // if there is a '-'
  if (m[2].matched) {
    return m[3].matched;
  } else {
    return !m[3].matched;
  }
}

int main() {
  string zip_pattern = "(\\d{5})(-)?(\\d{4})?";
  regex r(zip_pattern);
  
  ifstream infile("exercise17_23_input.txt");
  if (!infile) {
    cerr << "Error opening file\n";
    return 1;
  }

  string line;
  while(getline(infile, line)) {
    for(sregex_iterator it(line.begin(), line.end(), r), end_it; it!=end_it; ++it) {
      if (valid(*it)) {
        cout << "valid: " << it->str();
        // print last 4 digits if exist
        if ((*it)[3].matched) {
          cout << " (extension: " << (*it)[3] << ")";
        }
        cout << endl;
      } else {
        cout << "not valid: " << it->str() << endl;
      }
    }
  }
  
  return 0;
}
