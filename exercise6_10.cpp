// Using pointers, write a function to swap values of two ints
#include <iostream>

using namespace std;

void swap(int* a, int* b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int main() {
  int a = 2, b = 3;
  swap(&a, &b);
  cout << "a = " << a << "; b = " << b << endl;
  return 0;
}