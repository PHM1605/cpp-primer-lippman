// Use function objects, write a function to 
// "count number of values > 1024"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional> // for <bind> 

using namespace std;

int main() {
  vector<int> vec = {500,1500,2048,1000,1024,4096};
  int count = count_if(
    vec.begin(), 
    vec.end(),
    bind(greater<int>(), placeholders::_1, 1024)
  );
  cout << "Count > 1024: " << count << endl;
  return 0;
}