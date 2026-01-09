// Illustrate relationship between <size> and <capacity>

#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> ivec;
  // size() and capacity() of an empty ivec
  cout << "ivec: size: " << ivec.size() << "; capacity: " << ivec.capacity() << endl;

  // size() of 24 elements and capacity() of 32 elements
  for(vector<int>::size_type ix=0; ix != 24; ++ix)
    ivec.push_back(ix);
  cout << "ivec: size: " << ivec.size() << "; capacity: " << ivec.capacity() << endl;

  // reserve more space (size() still 24)
  ivec.reserve(50);
  cout << "ivec: size: " << ivec.size() << "; capacity: " << ivec.capacity() << endl;

  // fill vector with 0s for latter elements => size() and capacity() are both =50
  while(ivec.size() != ivec.capacity())
    ivec.push_back(0);
  cout << "ivec: size: " << ivec.size() << "; capacity: " << ivec.capacity() << endl;
  
  // add 1 more element => vector<int> must allocate more to 100
  ivec.push_back(42);
  cout << "ivec: size: " << ivec.size() << "; capacity: " << ivec.capacity() << endl;

  // TRY to reduce allocation (might not success)
  ivec.shrink_to_fit();
  cout << "ivec: size: " << ivec.size() << "; capacity: " << ivec.capacity() << endl;
  return 0;
}