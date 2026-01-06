// write a function that takes a pair of iterators to a vector<int> AND an integer
// returns iterator to requested element (nullptr if not found)
#include <iostream>
#include <vector>

using namespace std;

vector<int>::iterator check_int(vector<int>::iterator beg_iter, vector<int>::iterator end_iter, int val) {
  while(beg_iter != end_iter) {
    if (*beg_iter == val){
      return beg_iter;
    }
    beg_iter++;
  }
  return end_iter;
}

int main() {
  vector<int> vects = {3,6,8,1,2};
  vector<int>::iterator beg_iter = vects.begin()+1;
  vector<int>::iterator end_iter = vects.begin()+3;
  
  auto iter = check_int(beg_iter, end_iter, 2);

  if (iter != end_iter)
    cout << "value found: " << *iter << endl;
  else 
    cout << "value not found" << endl;
  
  return 0;
}