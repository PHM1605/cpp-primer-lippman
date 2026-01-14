// Use <reverse_iterator> to print a <vector> in reverse order
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> vi = {1,5,4,2};
  for (auto r_iter=vi.rbegin(); r_iter!=vi.rend(); r_iter++) {
    cout << *r_iter << endl;
  }
  return 0;
}