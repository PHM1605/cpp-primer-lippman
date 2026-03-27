// <dynamic_cast> and <typeid> example
#include <iostream>

using namespace std;

class Base {
  friend bool operator==(const Base&, const Base&);

public: 
  // interface members of Base
protected:
  virtual bool equal(const Base&) const;
};

class Derived: public Base {
public:
  // interface members of Derived
protected:
  bool equal(const Base&) const;
};

bool Base::equal(const Base& rhs) const {
  // do whatever is required to compare <Base> objects
  return true;
}
// NOTE: overriden <equal>; both terms are SURELY POINTING TO same type "Derived"
bool Derived::equal(const Base& rhs) const {
  auto r = dynamic_cast<const Derived&>(rhs); // convert Base& to Derived& then compare
  // do whatever to compare
  return true;
}

// OVERALL comparison
bool operator==(const Base& lhs, const Base& rhs) {
  // if right- and left-side are of same type, we compare
  return typeid(lhs)==typeid(rhs) && lhs.equal(rhs);
}

int main() { 
  Base b1, b2;
  Derived d1, d2;

  cout << boolalpha;
  cout << "b1==b2: " << (b1==b2) << endl;
  cout << "d1==d2: " << (d1==d2) << endl;
  cout << "b1==d1: " << (b1==d1) << endl;

  return 0;
}