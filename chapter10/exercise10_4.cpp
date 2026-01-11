// Use <accumulate> to sum elements in vector<double>
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
  vector<double> vd {1.0,4.0,5.0};
  int sum = accumulate(vd.begin(), vd.end(), 0);
  cout << sum << endl;
}