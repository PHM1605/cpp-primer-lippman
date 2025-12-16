// find_char: find location of first occurence + count #occurence
#include <iostream>
#include <string>

using namespace std;

string::size_type find_char(const string& s, char c, string::size_type &occurs) {
  auto ret = s.size();
  occurs = 0;
  for (decltype(ret) i=0; i!=s.size(); i++) {
    if (s[i] == c) {
      // when ret hasn't been set => set to 1st occurence
      if (ret==s.size()) {
        ret = i;
      }
      ++occurs;
    }
  }
  return ret;
}

int main() {
  string s = "This is a test string";
  char c = 's';
  string::size_type ctr = 0;
  auto index = find_char(s, c, ctr);
  if (ctr > 0)
    cout << "Character " << c << " occurs first at " << index << " then " << ctr << " times\n";
  else 
    cout << "Character " << c << " not found!\n";

  return 0;
}