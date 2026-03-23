// Use the unformatted version of <getline> to read a file
// Test by giving a file that contains empty lines; as well as lines longer than <char array> that passed to <getline>
#include <iostream>
#include <fstream>

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
    cout << "Read: [" << buffer << "]\n";
    cout << "gcount: " << in.gcount() << endl;

    if (in.fail() && !in.eof()) {
      cout << "Line too long for buffer\n";
      in.clear(); // clear failbit
      in.ignore(1000, '\n'); // skip the rest of the line OR upto 1000 chars
    }
    if (in.eof()) break;
  }

  return 0;
}