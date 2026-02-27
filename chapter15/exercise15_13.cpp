// Test <base> and <derived> print functions
#include <iostream>

using namespace std;

class base {
public:
  string name() { return basename; }
  virtual void print(ostream& os) {
    os << basename;
  }
private:
  string basename = "basename";
};

class derived: public base {
public:
  void print(ostream& os) override {
    base::print(os);
    os << " " << i;
  }
private:
  int i=1;
};

int main() {
  base bobj;
  derived dobj;
  base* bp1 = &bobj;
  base* bp2 = &dobj;
  base& br1 = bobj;
  base& br2 = dobj;

  bobj.print(cout);
  cout << endl;
  dobj.print(cout);
  cout << endl;

  cout << bp1->name() << endl;
  cout << bp2->name() << endl;

  br1.print(cout);
  cout << endl;
  br2.print(cout);
  cout << endl;
  return 0;
}