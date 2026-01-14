// Given a vector of 10 elements, copy the elements from positions 3 to 7 in reverse order to list
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

int main() {
  vector<int> vi = {0,1,2,3,4,5,6,7,8,9};
  list<int> li;
  copy(
    vi.rbegin() + (vi.size()-8), // 10-7-1
    vi.rbegin() + (vi.size()-3), // 10-3-1+1
    back_inserter(li) 
  );

  for (auto iter : li) {
    cout << iter << endl;
  }

}