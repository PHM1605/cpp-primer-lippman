// A method to control/monitor copy-control => printing out
#include <iostream>

using namespace std;

struct X {
  // default constructor
  X() {
    cout << "X()" << endl;
  }
  // constructor with another X
  X(const X&) {
    cout << "X(const X&)" << endl;
  }
  // copy-assignment operator
  X& operator=(const X& rhs) {
    cout << "operator=" << endl;
    return *this;
  }

  // destructor
  ~X() {
    cout << "~X()\n";
  }
};

int main() {
  X x1;
  X x2(x1);

  X x3;
  x3 = x1;
  
  return 0;
}