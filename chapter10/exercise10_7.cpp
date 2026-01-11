// Correct the errors in 2 examples
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int main() {
  // Example 2: because <reserve> does NOT create element
  vector<int> vec; 
  vec.reserve(10); // optional 
  // fill_n(vec.begin(), 10, 1); // WRONG
  fill_n(back_inserter(vec), 10, 1); // correction

  // debug
  for(auto& item: vec) {
    cout << item << " ";
  }
  cout << endl;
  return 0;
}