// Write <flip> that calls functions that have <lvalue> and <rvalue-reference> parameters
#include <iostream>

using namespace std;

template<typename F, typename T1, typename T2>
void flip_wrong(F f, T1&& t1, T2&& t2) {
  f(t2, t1);
}

template<typename F, typename T1, typename T2>
void flip_correct(F f, T1&& t1, T2&& t2) {
  f(
    std::forward<T2>(t2), // if T2 is "int"=>"int&&" inside
    std::forward<T1>(t1) // if T1 is "int&"=>"int&&&"="int&" inside
  );
}

void g(int&& i, int& j) {
  cout << i << " " << j << endl;
}

int main() {
  int i = 10;
  // wrong as i=t1="int&" and 42=t2=int inside
  // => inside g: i is "rvalue-ref" NOT MATCH to "lvalue" i.e. t2 being passed in
  // flip_wrong(g, i, 42);

  // when calling <g>: keep t1 (inside g) to be "int&"", t2 (inside g) to be "int"
  flip_correct(g, i, 42);

  return 0;
}