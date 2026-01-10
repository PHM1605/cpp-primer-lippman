// Write a function that takes 3 strings <s>, <oldVal>, <newVal>
// Use: <iterators>, <insert>, <erase> => replace <oldVal> in <s> by <newVal> (all occurences)
#include <iostream>
#include <string>

using namespace std;

void replace_all(string& s, string& oldVal, string& newVal) {
  for (auto it=s.begin(); it<=s.end()-oldVal.size();) {
    if (string(it, it+oldVal.size()) == oldVal) {
      it = s.erase(it, it+oldVal.size()); // return AFTER the last
      it = s.insert(it, newVal.begin(), newVal.end()); // insert BEFORE <it>; return pointer of FIRST inserted element
      // move after the new inserted
      it += newVal.size();
    } else {
      ++it;
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