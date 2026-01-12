// Correct the errors in 2 examples
#include <iostream>
#include <vector>
#include <iterator>
#include <list>

using namespace std;

int main() {
  // Example 1: Segmentation fault core dumped
  vector<int> vec1;
  list<int> lst1 {2,5,3,8,1};
  // copy(lst1.cbegin(), lst1.cend(), vec1.begin()); // WRONG: because we haven't allocated vec1
  copy(lst1.cbegin(), lst1.cend(), back_inserter(vec1));
  // debug
  for(auto& item: vec1) {
    cout << item << " ";
  }
  cout << endl;

  // Example 2: because <reserve> does NOT create element
  vector<int> vec2; 
  vec2.reserve(10); // optional 
  // fill_n(vec.begin(), 10, 1); // WRONG
  fill_n(back_inserter(vec2), 10, 1); // correction
  // debug
  for(auto& item: vec2) {
    cout << item << " ";
  }
  cout << endl;
  return 0;
}