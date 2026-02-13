// Create <HasPtr> with move-operators
#include <iostream>

using namespace std;

class HasPtr {
friend void swap(HasPtr&, HasPtr&);

public:
  // Constructor from a string
  HasPtr(const string& s = string()):
    ps(new string(s)), i(0) {}
  // Copy constructor
  HasPtr(const HasPtr& p):
    ps(new string(*p.ps)), i(p.i) {
    cout << "COPY CONSTRUCTOR\n";
  }

  // Move constructor
  HasPtr(HasPtr &&p) noexcept:
    ps(p.ps), i(p.i) {
    cout << "MOVE CONSTRUCTOR\n";
    p.ps = nullptr;
  }
  // BOTH copy- and move-assignment
  // - if a=rhs => <rhs> is COPIED-constructed
  // - if a=std::move(rhs) => <rhs> is MOVED-constructed 
  HasPtr& operator=(HasPtr rhs) {
    swap(*this, rhs); 
    return *this;
  }
  // Destructor
  ~HasPtr() { 
    cout << "DESTRUCTOR\n";
    delete ps; 
  }
  
  string& get_str() {
    return *ps;
  }

private: 
  string *ps;
  int i;
};

void swap(HasPtr& lhs, HasPtr& rhs) {
  cout << "Using swap\n";
  using std::swap;
  swap(lhs.ps, rhs.ps);
  swap(lhs.i, rhs.i);
}

HasPtr makeObj() {
  HasPtr temp("temporary");
  cout << "Returning from makeObj()\n";
  return temp;
}

int main() {
  cout << "\n--- Test 1: Copy constructor ---\n";
  HasPtr a("hello");
  HasPtr b(a);

  cout << "\n--- Test 2: Move constructor ---\n";
  HasPtr c(std::move(a));

  cout << "\n--- Test 3: Copy assignment ---\n";
  HasPtr d("world");
  HasPtr e("cpp");
  // <e> is "lvalue" => Copy assignment 
  // => <e> is passed by VALUE => extra Destructor after this call
  d = e; 

  cout << "\n--- Test 4: Move assignment ---\n";
  HasPtr f("move");
  HasPtr g("test");
  f = std::move(g);

  cout << "\n--- Test 5: Return value ---\n";
  HasPtr h = makeObj(); // RVO => return value optimization (no extra COPY)

  return 0;

}