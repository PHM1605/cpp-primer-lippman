// Define reference-counted version of <HasPtr>
#include "iostream"

using namespace std;

class HasPtr {
public:
  HasPtr(const string& s = string()):
    ps(new string(s)), i(0), use(new size_t(1)) {}
  // copy-constructor will point ALL objects to the same data; increase counter
  HasPtr(const HasPtr& p):
    ps(p.ps), i(p.i), use(p.use) {
      ++*use;
    }
  
  HasPtr& operator=(const HasPtr&);
  ~HasPtr();

  void debug(const char* name) const {
    cout << name << " -> value = " << *ps << ", use = " << *use << endl; 
  }
  string& get_string() {
    return *ps;
  }

private:
  string* ps;
  int i;
  size_t* use; // <ref-count> to track how many objects share
};

// Destructor decrease <ref-count> first, only delete when reaching 0
HasPtr::~HasPtr() {
  if (--*use == 0) {
    delete ps; // delete the common data of <string>
    delete use; // delete counter
  }
}

// Assignment - remember it's TWO steps:
// - increase counter for right-side
// - decrease (maybe delete) left-side
// Be careful with self-assigment
HasPtr& HasPtr::operator=(const HasPtr& rhs) {
  ++*rhs.use;
  // decrease, maybe delete left-hand
  if (--*use == 0) {
    delete ps;
    delete use;
  }
  // update left-hand to be right-hand
  ps = rhs.ps;
  i = rhs.i;
  use = rhs.use;
  return *this;
}

int main() {
  HasPtr h1("hello");
  h1.debug("h1");

  // create scope to test destructor
  {
    // test constructor
    HasPtr h2 = h1;
    h1.debug("h1");
    h2.debug("h2");
    // test copy assignent
    HasPtr h3;
    h3 = h1;
    h1.debug("h1");
    h3.debug("h3");
    // modify through 1 object => other two change too
    h2.get_string() = "HELLO";
    cout << "\nAfter modifying through h2:\n";
    h1.debug("h1");
    h2.debug("h2");
    h3.debug("h3"); 
  }

  // <h1> will be aware of the disappearance of <h2> and <h3>
  cout << "\nAfter h2 and h3 go out of scope:\n";
  h1.debug("h1");

  return 0;
}