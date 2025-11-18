// write swap function (swapping 2 integers) using reference
#include <iostream>

using namespace std;

void swap(int& a, int& b) {
  int tmp = a;
  a = b;
  b = tmp;
}

int main() {
  int a=2, b=3;
  swap(a, b);
  cout << "a=" << a << "; b=" << b << endl;

  return 0;
}