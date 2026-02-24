// Use function objects, write a function to 
// "multiply all values by 2"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional> // for <bind> 

using namespace std;

int main() {
  vector<int> vec = {1,5,6,2,8,0};
  transform(
    vec.begin(), 
    vec.end(),
    vec.begin(),
    bind(multiplies<int>(), placeholders::_1, 2) 
  );

  // print to test
  for(auto& val: vec) {
    cout << val << " ";
  }
  cout << endl;
  return 0;
}