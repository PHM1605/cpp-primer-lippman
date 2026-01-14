// Write a program using stream iterators to read a text file into vector<string>s
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <iostream>

using namespace std;

ostream& print(ostream& os, vector<string>& words) {
  for (auto& word: words) {
    os << word << " ";
  }
  os << endl;
  return os;
}

int main() {
  fstream fs ("exercise10_29_input.txt");
  istream_iterator<string> str_it(fs);
  istream_iterator<string> eof;

  // vector<string> words;
  // while(str_it != eof) {
  //   words.push_back(*str_it++);
  //   print(cout, words);
  // }

  // shorter way
  vector<string> words(str_it, eof);
  print(cout, words);

  return 0;
}