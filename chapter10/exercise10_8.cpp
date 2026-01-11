// Using <back_inserter> to FILL a vector WITHOUT allocating it first
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
  // Note: we haven't allocated anything here
  vector<int> vec;   
  fill_n(back_inserter(vec), 10, 2);

  // debug
  for(auto& item: vec) {
    cout << item << " ";
  }
  cout << endl;
  return 0;
}