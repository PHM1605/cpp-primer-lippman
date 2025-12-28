// Function: returns the shorter of 2 strings 
#include <iostream>
#include <string>

using namespace std;

const string& shorterString(const string& s1, const string& s2) {
  // NOTE: no copy is made to return <const string&> YET (but it's indeed <s1> or <s2>)
  return s1.size() <= s2.size() ? s1 : s2;
}

int main() {
  const string s1 = "This";
  const string s2 = "his";

  string shorter = shorterString(s1, s2); // NOTE: a copy of <s2> is made and assigned to <shorter> (which is a <string>)
  cout << "Shorter is \"" << shorter << "\"" << endl;

  return 0;
}