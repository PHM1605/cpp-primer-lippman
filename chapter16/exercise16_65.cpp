// Rewrite <debug_rep> with specialized templates
#include <iostream>
#include <sstream>

using namespace std;

template<typename T>
string debug_rep(const T& t) {
  ostringstream ret;
  ret << t;
  return ret.str();
}

// specialization
template<>
string debug_rep<const char*>(const char* const & str) {
  return debug_rep(string(str));
}

template<>
string debug_rep<char*>(char* const &str) {
  return debug_rep(string(str));
}

int main() {
  const char* p = "hello";
  char s[] = "world";
  cout << debug_rep(p) << endl;
  cout << debug_rep(s) << endl;
  
  return 0;
}