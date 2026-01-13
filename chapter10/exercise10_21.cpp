// Write a lambda that captures a local <int> and decrements that variable until it = 0
// Once it's 0 additional calls should no longer decrement that variable
// lambda should returns a <bool> that indicates whether that var =0
#include <iostream>

using namespace std;

void fcn() {
  int i = 4;
  auto f = [&i] () -> bool {
    if (i>0) 
      --i;
    return i == 0;
  };
  cout << f() << endl; // i=3 -> false
  cout << f() << endl; // i=2 -> false
  cout << f() << endl; // i=1 -> false
  cout << f() << endl; // i=0 -> true
  cout << f() << endl; // still 0 -> true
}

int main() {
  fcn();
}