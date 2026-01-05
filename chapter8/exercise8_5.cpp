// Write a function to open a file for input and read its WORDS into a vector of strings
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
  ifstream ifs("sales_data_input.txt");
  vector<string> out_words;
  string word;
  if (ifs) {
    while(ifs >> word) {
      out_words.push_back(word);
    }
  } else {
    cout << "Cannot open file" << endl;
  }

  // debug print
  cout << "Debug print:\n";
  for (auto& one_word : out_words) {
    cout << one_word << endl;
  }
  return 0;
}