// write a program to determine whether two vector<int>s are equal
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> v1 {1,2,4,3};
  vector<int> v2 {1,2,4,3};
  cout << (v1==v2) << endl;
  return 0;
}