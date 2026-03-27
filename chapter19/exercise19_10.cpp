// <typeid> and its returned <type_info> check for hierarchy tree
#include <iostream>

using namespace std;

class A {};
class B: public A {};
class C: public B {};

int main() {
  A* pa = new C;
  cout << typeid(pa).name() << endl;

  C cobj;
  A& ra = cobj;
  cout << typeid(&ra).name() << endl; // pointer of type <A> to a <C> object

  B* px = new B;
  A& ra2 = *px; // reference of type<A> to object of type <B>
  cout << typeid(ra2).name() << endl;

  return 0;
}