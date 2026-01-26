// An extending String class with a <string-pointer> and an <index>
#include <iostream>

using namespace std;

class HasPtr {
public:
  // construct with a <string>
  HasPtr(const string& s=string()):
    ps(new string(s)), i(0) {}
  // construct with copy-constructor
  HasPtr(const HasPtr& hptr):
    ps(new string(*hptr.ps)), i(0) {
      cout << "copy-constructor was used\n";
    }
  // assignment operator
  HasPtr& operator=(const HasPtr& hptr) {
    cout << "assignment operator was used\n";
    // protect against self-assignment
    if (this != &hptr) {
      delete ps; // NOTE: not having this will cause mem-leak
      ps = new string(*hptr.ps);
      i = hptr.i;
    }
    return *this;
  }
  // to debug
  void print() const {
    cout << "value = " << *ps << " with index " << i << endl;
  }
private:
  string* ps;
  int i;
};

int main() {
  HasPtr a("hello");
  HasPtr b = a;
  HasPtr c;
  c = a;

  a.print();
  b.print();
  c.print();
  return 0;
}