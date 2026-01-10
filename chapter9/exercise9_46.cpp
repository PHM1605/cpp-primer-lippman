// write a function that takes a string <name>, a string <prefix> (Mr. or Mrs), a string <postfix> (Jr. or III)
// Use <position>, <length> & <insert> => generate "Mr. Minh Jr." 
#include <iostream>
#include <string>

using namespace std;

void create_full_name(string& s, string& prefix, string& postfix) {
  // insert prefix
  s.insert(0, prefix + " ");
  // insert postfix
  s.insert(s.size(), " " + postfix);
}

int main() {
  string s = "Minh";
  string prefix = "Mr.";
  string postfix = "Jr.";

  create_full_name(s, prefix, postfix);
  cout << s << endl;
}