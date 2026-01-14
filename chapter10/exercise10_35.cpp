// Use normal to print a <vector> in reverse order
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> vi = {1,5,4,2};
  for (auto iter=vi.end()-1; iter>=vi.begin(); iter--) {
    cout << *iter << endl;
  }
  return 0;
}