// Add a destructor to <HasPtr> class
#include <iostream>

using namespace std;

class HasPtr {
public:
  // copy constructor
  HasPtr(const HasPtr& hptr):
    ps(new string(*hptr.ps)), i(hptr.i) {
      cout << "We are calling a copy constructor\n";
    }

  // constructor with a <string>
  HasPtr(const string& s = string()):
    ps(new string(s)), i(0) {
      cout << "We are calling constructor with a string\n";
    }

    // destructor
    ~HasPtr() {
      cout << "We are calling destructor\n";
      delete ps;
    }

private:
  string* ps;
  int i;
};

int main() {
  HasPtr hptr("Hello World");

  return 0;
}