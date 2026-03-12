// Create a clone of std::move function
#include <iostream>

using namespace std;

template <typename T>
typename remove_reference<T>::type&& move(T&& t) {
  return static_cast<typename remove_reference<T>::type&&>(t);
}

int main() {
  string s1("hi!"), s2;
  s2 = std::move(string("bye!"));
  s2 = std::move(s1);

  return 0;
}