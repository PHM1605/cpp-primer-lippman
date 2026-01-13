// Use <inserter>, <back_inserter> and <front_inserter> to copy a vector<int> of 9 elements to 3 empty containers
#include <vector>
#include <iostream>
#include <iterator>
#include <list>

using namespace std;

void print(vector<int>& vi) {
  for (auto i: vi) {
    cout << i << " ";
  }
  cout << endl;
}

void print(list<int>& vi) {
  for (auto i: vi) {
    cout << i << " ";
  }
  cout << endl;
}

int main() {
  vector<int> vi = {1,2,3,4,5,6,7,8,9};
  vector<int> vi_inserter;
  vector<int> vi_back_inserter;
  list<int> vi_front_inserter; // NOTE: <vector> does NOT have <push_front>

  copy(vi.begin(), vi.end(), inserter(vi_inserter, vi_inserter.begin()));
  copy(vi.begin(), vi.end(), back_inserter(vi_back_inserter));
  copy(vi.begin(), vi.end(), front_inserter(vi_front_inserter));

  print(vi_inserter);
  print(vi_back_inserter);
  print(vi_front_inserter);

  return 0;
}