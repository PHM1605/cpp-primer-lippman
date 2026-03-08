// Write <DebugDelete>
#include <iostream>

using namespace std;

class DebugDelete {
public:
  DebugDelete(ostream& s=cerr):
    os(s) {}
  // function calling "delete" on any pointer
  template<typename T>
  void operator()(T* p) const {
    os << "deleting unique_ptr" << endl;
    delete p;
  }
  
private:
  ostream& os;
};

int main() {
  double* p1 = new double;
  DebugDelete d1;
  d1(p1);

  int* ip2 = new int;
  d1(ip2);

  // to change the default <deleter> of a <unique_ptr>
  unique_ptr<int, DebugDelete> p2 (new int, DebugDelete());
  
  return 0;
}