// Write a program that use <unique_copy> to copy the unique elements from a <vector> to an empty <list>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>

using namespace std;

int main() {
  vector<int> vi {1,2,6,6,3,9};
  list<int> li;
  unique_copy(vi.begin(), vi.end(), back_inserter(li));
  // debug
  for (int i: li) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
}