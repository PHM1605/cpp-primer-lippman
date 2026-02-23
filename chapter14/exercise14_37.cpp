// Write a class object to test if two values are equal
// Use that object and library algorithm to write a program to replace all instance of a give value in a sequence
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class CheckEqual {
public:
  CheckEqual(int v): value(v) {}
  bool operator()(const int& a) {
    return a==value;
  }
private:
  int value; // value to check equal
};

int main() {
  vector<int> vect {1,4,7,8,4,0};

  // replace all "4" values with -1
  replace_if(vect.begin(), vect.end(), CheckEqual(4), -1);
  // display after
  for (auto it=vect.begin(); it!=vect.end(); it++) {
    cout << *it << " ";
  }
  cout << endl;
  
  return 0;
}