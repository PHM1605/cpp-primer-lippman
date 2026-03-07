// Write a <print> that handles an array of any type of any size
#include <iostream>

using namespace std;

template <typename ArrType, size_t N>
void print(ArrType (&a)[N]) {
  for (int i=0; i<N; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
}

int main() {
  int arr_int[] =  {1,2,7,4};
  print(arr_int);

  return 0;
}