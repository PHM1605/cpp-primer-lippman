// Add a number of "42" after each element
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> v {1,5,2,6};
  auto begin = v.begin();

  // NOTE: <insert> will INVALIDATE <end> 
  // so we can't put "auto end = v.end()" before the while loop 
  while(begin != v.end()) {
    // do something
    // insert new value e.g. of "42"
    ++begin;
    begin = v.insert(begin, 42); 
    ++begin;
  }

  // print debug 
  for (auto& val : v) {
    cout << val << " ";
  }
  cout << endl;
}