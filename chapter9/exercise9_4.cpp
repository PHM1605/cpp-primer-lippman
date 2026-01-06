// write a function that takes a pair of iterators to a vector<int> AND an integer
// returns whether that int value is in that pair range or not
#include <iostream>
#include <vector>

using namespace std;

bool check_int(vector<int>::iterator beg_iter, vector<int>::iterator end_iter, int val) {
  while(beg_iter != end_iter) {
    if (*beg_iter == val){
      return true;
    }
    beg_iter++;
       
  }
  return false;
}

int main() {
  vector<int> vects = {3,6,8,1,2};
  vector<int>::iterator beg_iter = vects.begin()+1;
  vector<int>::iterator end_iter = vects.begin()+3;
  cout << "value 8 in range? " << check_int(beg_iter, end_iter, 8) << endl;

  return 0;
}