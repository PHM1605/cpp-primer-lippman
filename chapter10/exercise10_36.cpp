// Use <find> to find the last element in a list of <int> with value 0
#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main() {
  list<int> li = {1,2,5,0,3,0,4};
  auto r_iter_0 = find(li.rbegin(), li.rend(), 0);
  if (r_iter_0 != li.rend()) {
    // Convert reverse iter => normal iter
    auto iter_0 = r_iter_0.base(); // the one AFTER the found
    --iter_0;
    // NOTE: <list> doesn't have random access => cannot subtract (-)
    cout << "Element number " << distance(li.begin(), iter_0) << endl;
  }
  
  return 0;
}