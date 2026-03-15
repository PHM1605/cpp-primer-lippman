// Variatic template with <sizeof...>
#include <iostream>

using namespace std;

template<typename T, typename ... Args>
void foo(const T& t, const Args& ... rest) {
  cout << "Total number of types: " << (1+sizeof...(Args)) << endl;
  cout << "Total number of arguments: " << (1+sizeof...(rest)) << endl;
}

int main() {
  int i=0;
  double d=3.14;
  string s="how now brown cow";

  foo(i, s, 42, d);
  foo(s, 42, "hi");
  foo(d, s);
  foo("hi");

  return 0;
}