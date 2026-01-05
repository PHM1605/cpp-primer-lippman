// Write a program to store each line from a file in a vector<string>
// Use <istringstream> to read each element from <vector> a word at a time 
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  ifstream infile("phone_data_input.txt");

  string line, word;
  vector<string> lines;

  // read all lines in file
  while (getline(infile, line)) {
    lines.push_back(line);
  }

  // use <istringstream> to read each line
  for (auto& line: lines) {
    istringstream iss(line);
    while (iss >> word) {
      cout << word << endl;
    }
  }

  return 0;
}