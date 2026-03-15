// <print> a random number of arguments => using RECURSION
#include <iostream>

using namespace std;

// print with fix number of arguments
template<typename T>
ostream& print(ostream& os, const T& t) {
  return os << t;
}
template<typename T, typename... Args>
ostream& print(ostream& os, const T& t, const Args... rest) {
  // print the 1st element
  os << t << ", ";
  return print(os, rest...);
}

int main() {
  int i=1;
  string s="hello";
  print(cout, i, s, 42);
  
  return 0;
}