// Write your own <begin> and <end> for an array
#include <iostream>

using namespace std;

template <typename T, size_t N>
T* my_begin(T (&a)[N]) {
  return a;
}

template <typename T, size_t N>
T* my_end(T (&a)[N]) {
  return a+N;
}

int main() {
  int arr[] = {1,4,6,3};
  for (auto iter=my_begin(arr); iter!=my_end(arr); iter++) {
    cout << *iter << " ";
  }
  cout << endl;

  return 0;
}