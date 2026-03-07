// Write a <constexpr> template that returns size of array
#include <iostream>

using namespace std;

template<typename T, size_t N>
constexpr size_t my_size(T (&a)[N]) { return N; }

int main() {
  int v[] = {1,2,4,7,0};
  cout << "Size of array is " << my_size(v) << endl;

  return 0;
}