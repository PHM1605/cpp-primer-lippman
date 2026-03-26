// Hierarchy tree example; why is there an error (NOTE: check "struct MI")
// Answer: inheritance does NOT overload functions with same name
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Base1 {
  void print(int) const;
protected:
  int ival;
  double dval;
  char cval;
};

struct Base2 {
  void print(double) const;
protected:
  double fval;
private: 
  double dval;
};

struct Derived: public Base1 {
  void print(string) const;
protected:
  string sval;
  double dval;
};

struct MI: public Derived, public Base2 {
  //NOTE: here is the fix
  using Base1::print;

  void print(vector<double>);
protected:
  int* ival;
  vector<double> dvec;
};

int main() {
  MI mi;
  mi.print(42);
}