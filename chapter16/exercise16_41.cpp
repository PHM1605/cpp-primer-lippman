// Write a version of sum() with a return type that is guaranteed to be large enough
#include <iostream>

using namespace std;

// NOTE: decltype(X) returns VALUE if X=<rvalue>; returns REF if X=<lvalue>
template<typename T>
auto my_sum(const T& a, const T& b) -> decltype(a+b) 
{
  return a+b;
}

int main() {
  cout << my_sum(3,4) << endl;
  cout << my_sum(3.5, 4.2) << endl;
  
  return 0;
}