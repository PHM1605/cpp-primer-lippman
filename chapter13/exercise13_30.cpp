// Write a <swap> function for value-like version of <HasPtr>
#include <iostream>

using namespace std;

class HasPtr {
friend void swap(HasPtr&, HasPtr&);

public:
  HasPtr(const string& s = string()):
    ps(new string(s)), i(0) {
      cout << "copy constructor\n";
    }
  HasPtr(const HasPtr& p):
    ps(new string(*p.ps)), i(p.i) {}
  HasPtr& operator=(const HasPtr&);
  ~HasPtr() { delete ps; }

private:
  string* ps;
  int i;
};

HasPtr& HasPtr::operator=(const HasPtr& rhs) {
  if (this != &rhs) {
    delete ps; // destroy left-hand first
    ps = new string(*rhs.ps); // clone value of right-hand to left-hand
    i = rhs.i;
  }
  return *this;
}

inline void swap(HasPtr& lhs, HasPtr& rhs) {
  // NOTE: this means std::swap() is a fallback
  // we PRIORITIZE swap(a,b) if a, b is of a NOT-BUILT-IN type
  // here it might not make a difference
  using std::swap;
  swap(lhs.ps, rhs.ps);
  swap(lhs.i, rhs.i);
}