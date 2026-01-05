// Write a function to open a file for input and read its content into a vector of strings
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
  ifstream ifs("sales_data_input.txt");
  vector<string> out_sentences;
  string line;
  if (ifs) {
    while(getline(ifs, line)) {
      out_sentences.push_back(line);
    }
  } else {
    cout << "Cannot open file" << endl;
  }

  // debug print
  cout << "Debug print:\n";
  for (auto& sent : out_sentences) {
    cout << sent << endl;
  }
  return 0;
}