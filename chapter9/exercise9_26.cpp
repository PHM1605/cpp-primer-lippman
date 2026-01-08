// copy <ia> into a <vector> and a <list>
// use <erase> to remove odd from <list>
// use <erase> to remove even from <vector>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {
  int ia[] = {0,1,1,2,3,5,8,133,21,55,89};
  // copy <ia> into a <vector> and a <list>
  vector<int> vi;
  list<int> li;
  for (auto& num : ia) {
    vi.push_back(num);
    li.push_back(num);
  }

  // use single-iterator form of <erase> to remove odd from <list>
  for (auto iter=li.begin(); iter != li.end();) {
    if ((*iter) % 2 == 0) {
      iter = li.erase(iter);
    } else {
      iter++;
    }
  }
  // use single-iterator form of <erase> to remove even from <list>
  for (auto iter=vi.begin(); iter!=vi.end();) {
    if ((*iter % 2) == 1) {
      iter = vi.erase(iter);
    } else {
      iter++;
    }
  }

  // print to check
  for (auto& num: li) {
    cout << num << " ";
  }
  cout << endl;

  for (auto& num: vi) {
    cout << num << " ";
  }
  cout << endl;
}