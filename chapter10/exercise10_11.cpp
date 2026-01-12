// Write a program that uses <stable_sort> and <isShorter> 
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
  // sort in ALPHABETICAL ORDER
  // fox/jumps/over/quick/red/red/slow/the/the/turtle
  sort(words.begin(), words.end());

  // put unique portion at start; duplicated entries at the end
  // return iterator one-pass-unique-part
  // fox/jumps/over/quick/red/slow/the/turtle/???/???
  auto end_unique = unique(words.begin(), words.end());

  // erase duplications
  words.erase(end_unique, words.end());
}

// predicate to pass to <stable_sort> function
bool isShorter(const string& s1, const string& s2) {
  return s1.size() < s2.size();
}

int main() {
  // prepare data
  string input_str = "the quick red fox jumps over the slow red turtle";
  stringstream ss(input_str);
  string word;
  vector<string> words;
  while(ss >> word) {
    words.push_back(word);
  }

  // <isShorter>: sort in WORD SIZE ORDER 
  // <stable_sort>: main ALPHABETICAL ORDER
  elimDups(words);
  stable_sort(words.begin(), words.end(), isShorter);
  print_vec(words);

  return 0;
}