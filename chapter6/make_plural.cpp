// Write a function: return plural of <word> if counter <ctr> is greater than 1
#include <iostream>
#include <string>

using namespace std;

string make_plural(size_t ctr, const string& word, const string &ending) {
  return (ctr>1) ? word+ending : word; // this returns a copy of <const string&> to <string>
}

int main() {
  cout << make_plural(2, "apple", "s") << endl;

  return 0;
}