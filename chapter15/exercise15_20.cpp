// Write classes to test inheritance access
#include <iostream>

using namespace std;

class Base {
public:
  void pub_mem() { cout << "Base public\n"; }
protected:
  int prot_mem=1;
private:
  char priv_mem='a';
};

struct Pub_Derv: public Base {
  int f() { return prot_mem; } // ok: derived can access protected
  // char g() { return priv_mem; } // not ok: derived can't access private

  void memfcn(Base& b) { b = *this; }
};

struct Prot_Derv: protected Base {
  int f2() const { return prot_mem; } // still ok

  void memfcn(Base& b) { b = *this; } // still ok; as this is protected of Base
};

struct Priv_Derv: private Base {
  int f1() const { return prot_mem; } // still ok: private derivation only affects OUTSIDE usage

  void memfcn(Base& b) { b = *this; } // still ok: private derivation only affects OUTSIDE usage
};

struct Derived_from_Public: public Pub_Derv {
  int use_base() { return prot_mem; }
};

struct Derived_from_Protected: public Prot_Derv {

};

struct Derived_from_Private: public Priv_Derv {
  // int use_base() { return prot_mem; } // error
};

int main() {
  Pub_Derv d1; 
  Prot_Derv d3;
  Priv_Derv d2;
  Base* p = &d1;
  // p = &d2; // not ok
  // p = &d3; // not ok

  Derived_from_Public dd1;
  p = &dd1;

  // Derived_from_Private dd2;
  // p = &dd2; // not ok

  // Derived_from_Protected dd3;
  // p = &dd3; // not ok

  return 0;
}