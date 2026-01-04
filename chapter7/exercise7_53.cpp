// Debug class 
#include <iostream>
using namespace std;

class Debug {
public:
  constexpr Debug(bool b=true): hw(b), io(b), other(b) {}
  constexpr Debug(bool h, bool i, bool o): hw(h), io(i), other(o) {}

  constexpr bool any() const { return hw || io || other; }
  void set_io(bool b) { io = b; }
  void set_hw(bool b) { hw = b; }
  void set_other(bool b) { hw = b; }

private:
  bool hw; // flagging error is hardware or not
  bool io; // flagging error is IO or not
  bool other; // flagging other error
};

int main() {
  // debugging IO
  constexpr Debug io_sub(false, true, false);
  if (io_sub.any()) {
    cerr << "print appropriate error message" << endl;
  }
  
  const Debug prod(false); // no debugging during production
  if(prod.any()) {
    cerr << "print an error message" << endl;
  }
  
  return 0;
}