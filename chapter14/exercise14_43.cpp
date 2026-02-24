// Using library function objects, determine whether a given <int> is divisible by any element in vector<int>
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

int main() {
  vector<int> divisors = {3,5,7};
  int value = 35;
  bool divisible = any_of(
    divisors.begin(),
    divisors.end(),
    bind(
      equal_to<int>(),
      bind(modulus<int>(), value, placeholders::_1),
      0)
  );

  // print out to check
  if (divisible)
    cout << value << " is divisible by at least one element.\n";
  else 
    cout << value << " is NOT divisible by any element.\n";

  return 0;
}