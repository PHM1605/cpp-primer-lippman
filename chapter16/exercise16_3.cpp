// Write a clone of <find> function
#include <iostream>
#include <vector>
#include <list>

using namespace std;

template <typename Iterator, typename T>
Iterator my_find(Iterator begin, Iterator end, const T& val) {
  for(auto iter=begin; iter!=end; iter++) {
    if(*iter==val) {
      return iter;
    }
  }
  return end;
}

int main() {
  // find element from vector
  vector<int> v {1,2,6,3,8};
  auto loc1 = my_find(v.begin(), v.end(), 3);
  if (loc1 == v.end())
    cout << "3 not found\n";
  else
    cout << "Found " << *loc1 << " at location " << loc1-v.begin() << endl;

  // find element from list
  list<string> ls_str { "abc", "de", "zyz"};
  auto loc2 = my_find(ls_str.begin(), ls_str.end(), string("zz"));
  if (loc2 == ls_str.end())
    cout << "String not found\n";
  else
    cout << "Found " << *loc2 << " at location " << distance(loc2, ls_str.begin()) << endl;

  return 0;
}