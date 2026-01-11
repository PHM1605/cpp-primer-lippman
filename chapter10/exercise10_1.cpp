// Use the <count> ints function
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  vector<int> vi = {1,4,6,2,5,4,3};
  int val = 4;
  auto result = count(vi.begin(), vi.end(), val);
  cout << result << endl;
  return 0;
}