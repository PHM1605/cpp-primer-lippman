// multiset example
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
  // vector<int>: {0,0,1,1,2,2,....,9,9}
  vector<int> ivec;
  for (vector<int>::size_type i=0; i!=10; i++) {
    ivec.push_back(i);
    ivec.push_back(i);
  }
  // <iset> holds unique elements; <miset> holds all
  set<int> iset(ivec.cbegin(), ivec.cend());
  multiset<int> miset(ivec.cbegin(), ivec.cend());

  // print
  cout << ivec.size() << endl;
  cout << iset.size() << endl;
  cout << miset.size() << endl;

  return 0;
}