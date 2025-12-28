// Write a recursive function to print the contents of a vector
#include <iostream>
#include <vector>

using namespace std;

void print_content(vector<int>& v, int index=0) {
  if (index>=v.size())
    return;
  cout << v[index] << " ";
  print_content(v, index+1);
}

int main() {
  vector<int> v {3,4,1,0,2};
  print_content(v);
  return 0;
}