// write a program to determine whether a list<int> and vector<int> are equal
#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main() {
  vector<int> vi {1,2,4,3};
  list<int> li {1,2,4,3};

  // create a conversion vector from list<int> to vector<int>
  vector<int> vi2;
  vi2.assign(li.begin(), li.end());
  
  cout << (vi==vi2) << endl;
  return 0;
}