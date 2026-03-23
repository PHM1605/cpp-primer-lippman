// 2nd way to handle correctly when exception is thrown: <unique_ptr>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

using namespace std;

void exercise(int* b, int* e) {
  vector<int> v(b, e);
  // unique pointer to array of ints
  // NOTE: will automatically clean <p> in any case
  unique_ptr<int[]> p(new int[v.size()]); 
  ifstream in("ints"); // exception occurs here
  if (!in) throw runtime_error("file open failed");
  // simulate work
  cout << "Processing with unique_ptr...\n";
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