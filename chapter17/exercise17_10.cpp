// <bitset> initialization from a sequence of indices
#include <iostream>
#include <bitset>

using namespace std;

int main() {
  // direct initialization
  bitset<32> bs1 (
    (1<<1) | (1<<2) | (1<<3) | (1<<5) | (1<<8) | (1<<13) | (1<<21)
  );
  cout << "bitset1: " << bs1 << endl;

  // initialization from a sequence
  bitset<32> bs2;
  int seq[] = {1,2,3,5,8,13,21};
  for (int n: seq) 
    bs2.set(n);
  cout << "bitset2: " << bs2 << endl;

  return 0;
}