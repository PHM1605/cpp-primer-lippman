// Write a function that takes 3 strings <s>, <oldVal>, <newVal>
// Use: <iterators>, <index>, <replace> => replace <oldVal> in <s> by <newVal> (all occurences)
#include <iostream>
#include <string>

using namespace std;

void replace_all(string& s, string& oldVal, string& newVal) {
  for (int i=0; i<=(s.size()-oldVal.size());) {
    string sub(s, i, oldVal.size());
    if (sub == oldVal) {
      s.replace(i, oldVal.size(), newVal);
      // move after the new inserted
      i += newVal.size();
    } else {
      ++i;
    }
  }
}

int main() {
  string s = "I went thru this book even tho it's very tough to go thru";
  string oldVal = "thru";
  string newVal = "through";

  replace_all(s, oldVal, newVal);
  cout << s << endl;

  return 0;
}