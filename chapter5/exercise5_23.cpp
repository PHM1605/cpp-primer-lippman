// Write a program that reads two integers from stdin and prints the result
#include <iostream>

using namespace std;

int main() {
  float a, b;
  cout << "Enter two numbers: ";
  while(cin) {
    try {
      cin >> a >> b;
      if (b==0) {
        throw runtime_error("Denominator must be different from 0");
      }
      cout << a/b << endl;
      cout << "Enter two numbers: ";
    } catch(runtime_error err) {
      cout << err.what() << endl;
      cout << "Enter two numbers: ";
    }    
  }
  
  return 0;
}