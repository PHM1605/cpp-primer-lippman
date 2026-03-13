// Check overloaded template functions
#include <iostream>

using namespace std;

template<typename T>
void f(T) {
  cout << "Calling f(T)\n";
}

template<typename T>
void f(const T*) {
  cout << "Calling f(const T*)\n";
}

template<typename T>
void g(T) {
  cout << "Calling g(T)\n";
}

template <typename T>
void g(T*) {
  cout << "Calling g(T*)\n";
}

int main() {
  int i=42, *p = &i;
  const int ci=0, *p2 = &ci;

  f(42);
  f(p); // exact match => f(T) with T=int*
  f(ci);
  f(p2);

  g(42);
  g(p);
  g(ci); 
  g(p2);

  return 0;
}