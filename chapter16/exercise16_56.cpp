// Write a variadic version of <errorMsg>
#include <iostream>
#include <sstream>

using namespace std;

template<typename T>
string debug_rep(const T& t) {
  ostringstream ret;
  ret << t;
  return ret.str(); // return a copy of the string
}

template<typename T>
ostream& print(ostream& os, const T& t) {
  return os << t;
}

template<typename T, typename ... Args>
ostream& print(ostream& os, const T& t, const Args&... rest) {
  os << t << ", ";
  return print(os, rest...);
}

template<typename... Args>
ostream& errorMsg(ostream& os, const Args& ... rest) {
  return print(os, debug_rep(rest)...);
}

int main() {
  errorMsg(cerr, "test_fcn", 32, 1.4);

  return 0;
}