// Define hierarchy tree Class->Base->virtual D1/virtual D2->MI->Final
#include <iostream>

using namespace std;

class Class {
public:
  Class() { cout << "Class default\n"; }
  Class(int v) { cout << "Class(int) with " << v << endl; }
  Class(const Class&) { cout << "C copy\n"; }
};

class Base: public Class {
public:
  Base(): Class(), x(0) { cout << "Base default\n"; }
  Base(int v): Class(v), x(v) { cout << "Base(int)\n"; }
  Base(const Base& other): Class(other), x(other.x) { cout << "Base copy\n"; }
private:
  int x;
};

class D1: virtual public Base {
public: 
  D1() { cout << "D1 default\n"; }
  D1(int v): Base(v) { cout << "D1(int)\n"; }
  D1(const D1& other): Base(other) { cout << "D1 copy\n"; }
};

class D2: virtual public Base {
public:
  D2() { cout << "D2 default\n"; }
  D2(int v): Base(v) { cout << "D2(int)\n"; }
  D2(const D2& other): Base(other) { cout << "D2 copy\n"; }
};

class MI: public D1, public D2 {
public:
  MI(): Base(), D1(), D2() { cout << "MI default\n"; }
  MI(int v): Base(v), D1(v), D2(v) { cout << "MI(int)\n"; } // NOTE: we must construct NONDIRECT BASE here
  MI(const MI& other):
    Base(other), D1(other), D2(other) { cout << "MI copy\n"; }
};

class Final: public MI {
public:
  Final(): Base(), MI() { cout << "Final default\n"; }
  Final(int v): Base(v), MI(v) { cout << "Final(int)\n"; } // NOTE: we must construct NONDIRECT BASE here
  Final(const Final& other): Base(other), MI(other) { cout << "Final copy\n"; }
};

int main() {
  Final f(10);
  return 0;
}