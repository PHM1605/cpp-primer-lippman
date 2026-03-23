// Write a program that INSERTS a line at the end of a text file
// indicating starting OFFSET of each line (excluding the 1st, which always be 0)
#include <iostream>
#include <fstream>

using namespace std;

int main() {
  // in, out: file is opened for BOTH input & output
  // ate:: seek to EOF immediately after open
  fstream inOut("exercise17_39.txt", fstream::ate | fstream::in | fstream::out);
  if (!inOut) {
    cerr << "Unable to open file!" << endl;
    return EXIT_FAILURE;
  }
  // file is opened in <ate> mode => saving the EOF location
  auto end_mark = inOut.tellg();
  // reposition to start-of-file
  inOut.seekg(0, fstream::beg);

  // check stream is valid AND having reached <end_mark> or not AND we can still get a line
  string line;
  size_t cnt = 0; // number of chars from the beginning
  while(inOut && inOut.tellg()!=end_mark && getline(inOut, line)) {
    cnt += line.size() +1; // +1 for '\n' at the end
    auto mark = inOut.tellg(); // start of next line after <getline>
    // put write marker to very-end-of-file => write <offset> number
    inOut.seekp(0, fstream::end);
    inOut << cnt;
    // print a separator if not last line
    if (mark != end_mark) {
      inOut << " ";
    }
    inOut.seekg(mark);
  }
  // Write a '\n' at the end of last (i.e. output) line
  inOut.seekp(0, fstream::end);
  inOut << "\n";

  return 0;
}