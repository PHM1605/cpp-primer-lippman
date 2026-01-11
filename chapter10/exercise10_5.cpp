// Use <equal> of <algorithm> on C-style string (instead of library's <string>)
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int main() {
  const char* roster1 = "This is a test string";
  const char* roster2 = "This is a test string";
  bool same = equal(roster1, roster1+strlen(roster1), roster2);
  cout << "Same? " << same << endl;
  return 0;
}