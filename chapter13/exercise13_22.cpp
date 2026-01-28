// Write a <HasPtr> class to behave like a "value"
#include <iostream>

using namespace std;

class HasPtr {
public:
  HasPtr(const string& s=string()):
    ps(new string(s)), i(0) {
      cout << "copy constructor\n";
    }
  // to behave like "value"
  HasPtr(const HasPtr& p):
    ps(new string(*p.ps)), i(p.i) {}
  HasPtr& operator=(const HasPtr&);
  ~HasPtr() { 
    delete ps; 
    cout << "destructor\n";
  }

private:
  string* ps;
  int i;
};

HasPtr& HasPtr::operator=(const HasPtr& rhs) {
  cout << "copy assignment\n";
  // NOTE: we must take into account "self-assignment" i.e. can't delete left-hand-side then right is deleted too
  auto newp = new string(*rhs.ps); // ... must copy-construct first
  delete ps;
  ps = newp;
  i = rhs.i;
  return *this;
}

int main() {
  HasPtr a("hello");
  HasPtr b = a; // copy constructor
  HasPtr c("world");

  c = a; // copy assignmen - c now should be "hello"
  cout << "Initial copies done.\n";

  // self-assignment test
  a = a;
  cout << "Self-assignment completed.\n";

  // Scope test: destructor will run at end
  cout << "End of main.\n";

  return 0;
}