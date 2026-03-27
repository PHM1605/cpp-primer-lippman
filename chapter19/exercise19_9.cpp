// <typeid> and its returned <type_info> check
#include <iostream>

using namespace std;

class Base {};
class Derived: public Base {};
class Sales_data {};

int main() {
  int arr[10];
  Derived d;
  Base* p = &d;

  cout << typeid(42).name() << endl;
  cout << typeid(arr).name() << endl;
  cout << typeid(Sales_data).name() << endl;
  cout << typeid(std::string).name() << endl;
  cout << typeid(p).name() << endl;
  cout << typeid(*p).name() << endl;

  return 0;
}