// 1st way to handle correctly when exception is thrown: several throw-catch
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void exercise(int* b, int* e) {
  vector<int> v(b, e);
  int* p = new int[v.size()]; // pointer to array of ints => need proper cleanup
  try {
    ifstream in("ints"); // exception occurs here
    if (!in) throw runtime_error("file open failed");
    // simulate work
    cout << "Processing with raw pointer...\n";
  } catch(...) {
    delete[] p; // cleanup
    throw; // rethrow
  }
  delete[] p; // cleanup
}

int main() {
  int arr[] = {1,2,3,4,5};
  try {
    exercise(arr, arr+5);
  } catch(const exception& e) {
    cout << "Caught: " << e.what() << endl;
  }
  return 0;
}