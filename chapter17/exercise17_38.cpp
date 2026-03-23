// Use the unformatted version of <getline> to read a file
// EXTENDED: write each word into its own line
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
  ifstream in("exercise17_37_input.txt");
  if (!in) {
    cerr << "Cannot open file\n";
    return 1;
  }

  const int SIZE = 10; // intentionally small to trigger edge cases
  char buffer[SIZE];
  while (true) {
    // get line-by-line into <buffer>
    in.getline(buffer, SIZE);
    
    // read each word in a line
    istringstream iss(buffer);
    string word;
    while(iss >> word) {
      cout << word << endl;
    }

    if (in.fail() && !in.eof()) {
      cout << "Line too long for buffer\n";
      in.clear(); // clear failbit
      in.ignore(1000, '\n'); // skip the rest of the line OR upto 1000 chars
    }
    if (in.eof()) break;
  }

  return 0;
}