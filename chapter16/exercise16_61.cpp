// Write your own version of <make_shared>
#include <iostream>
#include <memory>

using namespace std;

template<typename T, typename... Args>
shared_ptr<T> my_make_shared(Args&&... args) {
  return shared_ptr<T>(new T(std::forward<Args>(args)...));
}

int main() {
  // create pointer-to-"aaaaaaaaaa"
  shared_ptr<string> ps = my_make_shared<string>(10, 'a');
  cout << *ps << endl;
  
  return 0;
}