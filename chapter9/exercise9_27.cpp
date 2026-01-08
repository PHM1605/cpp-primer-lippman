// Write a program to find and remove odds from forward_list<int>
#include <iostream>
#include <forward_list>

using namespace std;

int main() {
  forward_list<int> flst =  {0,1,2,3,4,5,6,7,8,9};
  // to use <forward_list> we must keep track of 2 iterators
  auto prev = flst.before_begin();
  auto curr = flst.begin();
  while(curr != flst.end()) {
    // remove odd. NOTE: the <erase_after> only moves <curr>, keep old <prev>
    if (*curr % 2) {
      curr = flst.erase_after(prev);
    } else {
      prev = curr;
      curr++;
    }
  }


  return 0;
}