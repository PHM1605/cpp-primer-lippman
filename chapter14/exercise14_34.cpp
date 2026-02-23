// Create a function object, taking 3 params
// if <1st>==true => returns <2nd>, otherwise <3rd>
#include <iostream>

using namespace std;

class FunctionObject {
public:
  string operator()(bool first, const string& second, const string& third) {
    if (first) {
      return second;
    } else {
      return third;
    }
  }
};

int main() {
  FunctionObject func_obj;
  cout << func_obj(true, "true", "false") << endl;

  return 0;
}