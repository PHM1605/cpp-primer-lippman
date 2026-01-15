// Write program to eliminate duplicated words USING <list>
#include <iostream>
#include <list>
#include <string>

using namespace std;

void print_lst(list<string>& words) {
  for (auto& word: words) {
    cout << word << " ";
  }
  cout << endl;
}

void elimDups(list<string>& words) {
  // sort in alphabetical order
  words.sort();
  print_lst(words);
  // make unique a sorted list
  words.unique();
  print_lst(words);
}

int main() {
  list<string> ls {"this", "is", "a", "test", "test", "string"};
  elimDups(ls);
  return 0;
}