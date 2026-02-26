// Write the class <SmallInt>
#include <iostream>

using namespace std;

class SmallInt {
  // friend SmallInt operator+(const SmallInt&, const SmallInt&);
public:
  SmallInt(int i=0): val(i) {
    if (i<0 || i>255) {
      throw out_of_range("Bad SmallInt value");
    }
  }
  operator int() const { return val; } // convert <SmallInt> to <int>

private:
  size_t val;
};

// SmallInt operator+(const SmallInt& a, const SmallInt& b) {
//   return a+b;
// }

int main() {
  SmallInt si;
  si = 4;
  si = si+3.14;
  cout << si << endl;

  return 0;
}