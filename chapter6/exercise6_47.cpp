// Write a recursive function to print contents of a vector AND its length in debug mode
// to turn on NDEBUG e.g. ignore debugging print: 
// g++ -D NDEBUG exercise6_47.cpp
#include <iostream>
#include <vector>

using namespace std;

void print_content(vector<int>& v, int index=0) {
  if (index>=v.size())
    return;
  cout << v[index] << "\n";
  
  print_content(v, index+1);
  #ifndef NDEBUG
  cout << "The length of vector is " << v.size() << "\n";
  #endif
}

int main() {
  vector<int> v{3,4,1,0,2};
  print_content(v);
  return 0;
}