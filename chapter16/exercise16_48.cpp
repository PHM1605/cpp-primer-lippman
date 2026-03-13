// Write <debug_rep>
#include <iostream>
#include <sstream>

using namespace std;

// General
template<typename T>
string debug_rep(const T& t) {
  ostringstream ret; 
  ret << t;
  return ret.str();
}

// To debug by printing pointer AND the corresponding object
template<typename T>
string debug_rep(T* p) {
  ostringstream ret;
  ret << "pointer: " << p;
  if (p)
    ret << " " << debug_rep(*p);
  else
    ret << " null pointer";
  return ret.str();
}

// non-template
string debug_rep(const string& s) {
  return '"' + s + '"';
}
string debug_rep(char* p) {
  return debug_rep(string(p));
}
string debug_rep(const char* p) {
  return debug_rep(string(p));
}

int main() {
  string s("hi");
  cout << debug_rep(s) << endl; // call 1st "debug_rep" is 3rd "debug_rep" is commented out; otherwise 3rd
  cout << debug_rep(&s) << endl; // call 2nd "debug_rep"

  // calling C-style character string => best match is "debug_rep<T>(T*)" ONLY IF non-templates are not defined
  cout << debug_rep("hi world!") << endl;

  return 0;
}