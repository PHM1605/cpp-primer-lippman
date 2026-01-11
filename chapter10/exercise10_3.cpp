// Use <accumulate> to sum elements in vector<int>
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
  vector<int> vi {1,4,5};
  int sum = accumulate(vi.begin(), vi.end(), 0);
  cout << sum << endl;
}