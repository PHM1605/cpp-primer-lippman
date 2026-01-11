// Using <fill_n>, write a program to set a sequence of ints to 0
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  vector<int> vi {1,3,5,6,7};
  fill_n(vi.begin(), vi.size(), 0);

  // print out to debug
  for (auto& item: vi) {
    cout << item << " ";
  }
  cout << endl;
  return 0;
}