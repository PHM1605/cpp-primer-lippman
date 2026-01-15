// Write your own version of <elimDups>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

void print_vec(vector<string>& words) {
  for (auto &word : words) {
    cout << word << " ";
  }
  cout << endl;
}

void elimDups(vector<string>& words) {
  // sort in alphabetical order
  
  sort(words.begin(), words.end()); 
  print_vec(words);

  // put unique portion at start; duplicated entries at end
  // return iterator one-pass-unique-part
  // fox/jumps/over/quick/red/slow/the/turtle/???/???
  auto end_unique = unique(words.begin(), words.end());
  print_vec(words);

  // erase duplications
  words.erase(end_unique, words.end());
  print_vec(words);
}

int main() {
  string input_str = "the quick red fox jumps over the slow red turtle";
  stringstream ss(input_str);
  string word;
  vector<string> words;
  while(ss >> word) {
    words.push_back(word);
  }

  elimDups(words);
  return 0;
}