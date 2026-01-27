// Create a class with id number generated each time called
#include <iostream>

using namespace std;

class numbered {
public:
  static size_t count;
  // copy-control members (constructor and assignment)
  numbered(): mysn(count++) {}
  numbered& operator=(const numbered& new_num) {
    // other members of that <new_num> might be copied here; but not ID
    return *this;
  }

  size_t mysn;
};

size_t numbered::count = 0;

void f(const numbered& s) {
  cout << s.mysn << endl;
}

int main() {
  numbered a, b=a, c=b;
  f(a);
  f(b);
  f(c);
  return 0;
}