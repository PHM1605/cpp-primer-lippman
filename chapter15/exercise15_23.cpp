#include <iostream>

using namespace std;

class Base {
public:
  virtual int fcn();
};

class D1: public Base {
public:
  int fcn() override;
  int fcn(int);
  virtual void f2();
};

class D2: public D1 {
public:
  int fcn(int); // override D1::fcn(int)
  int fcn(); // override Base::fcn()
  void f2(); // override D1::f2() 
};
