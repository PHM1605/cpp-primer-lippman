// from <vector>: remove even, duplicate odd
// from <list>: remove even, duplicate odd
#include <iostream>
#include <vector>
#include <list>

using namespace std;

template<typename Container>
void even_remove_odd_dup(Container& c) {
  auto iter = c.begin();
  while (iter != c.end()) {
    if (*iter % 2 == 1) {
      // insert BEFORE <iter>; returns that inserted location
      iter = c.insert(iter, *iter);
      // NOTE: we must do this instead of "iter += 2" because <list> doesn't support that (although <vector> does)
      ++iter;
      ++iter;
    } else {
      // do NOT increase <iter> here; as it returns the location of NEXT element
      iter = c.erase(iter);
    }
  }
}

int main() {
  vector<int> vi = {0,1,2,3,4,5,6,7,8,9};
  list<int> li = {0,1,2,3,4,5,6,7,8,9};
  even_remove_odd_dup(vi);
  even_remove_odd_dup(li);

  // debug
  for (auto& num: vi) {
    cout << num << " ";
  }
  cout << endl;

  for (auto& num: li) {
    cout << num << " ";
  }
  cout << endl;

  return 0;
}