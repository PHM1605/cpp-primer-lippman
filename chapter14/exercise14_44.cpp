// Write a simple desk calculator program
#include <iostream>
#include <map>
#include <functional>

using namespace std;

// function/function pointer
int add(int i, int j) {
  return i+j;
}
// lambda
auto mod = [](int i, int j) {
  return i%j;
};
// function-object
struct divi {
  int operator()(int numerator, int divisor) {
    return numerator / divisor;
  }
};

int main() {
  map<string, function<int(int,int)>> binops = {
    {"+", add}, // function pointer
    {"-", minus<int>()}, // library function-object
    {"/", divi()}, // user-define function object
    {"*", [](int i, int j) { return i*j; }}, // unnamed lambda
    {"%", mod} // named lambda above
  };

  // Print to test calculator
  cout << binops["+"](10,5) << endl;
  cout << binops["-"](10,5) << endl;
  cout << binops["/"](10,5) << endl;
  cout << binops["*"](10,5) << endl;
  cout << binops["%"](10,5) << endl;

  return 0;
}