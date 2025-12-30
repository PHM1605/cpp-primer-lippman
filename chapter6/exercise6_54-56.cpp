#include <iostream>
#include <vector>

using namespace std;

// Exercise 6.54: Write a declaration for a function that takes 2 ints and returns an int.
// then declare a vector whose elements have this function POINTER type
using math_op = int (*)(int, int); // using type alias
vector<math_op> ops;

// Exercise 6.55: Write <add>, <subtract>, <multiply>, <divide> and store in <vector>
int add(int a, int b) {
  return a+b;
}

int subtract(int a, int b) {
  return a-b;
}

int multiply(int a, int b) {
  return a*b;
}

int divide(int a, int b) {
  return a/b;
}

int main() {
  int a = 9, b = 2;

  ops.push_back(&add);
  ops.push_back(&subtract);
  ops.push_back(multiply);
  ops.push_back(divide);

  for (auto op : ops) {
    cout << op(a,b) << endl;
  }
  return 0;
}