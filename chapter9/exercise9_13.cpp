// How to initialize a vector<double> from list<int>?
// How to initialize a vector<double> from vector<int>?
#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main() {
  // initialize a vector<double> from list<int>
  list<int> li = {1,2,5,6,0};
  vector<double> vd1(li.begin(), li.end());

  // initializer a vector<double> from vector<int>
  vector<int> vi = {1,2,5,6,0};
  vector<double> vd2(vi.begin(), vi.end());

  // print out to check
  for (auto beg=vd1.begin(); beg != vd1.end(); beg++) {
    cout << *beg << " ";
  } 
  cout << endl; 

  for (auto beg=vd2.begin(); beg != vd2.end(); beg++) {
    cout << *beg << " ";
  } 
  cout << endl; 

  return 0;
}