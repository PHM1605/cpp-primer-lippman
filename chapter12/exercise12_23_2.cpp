// Write a program to concatenate 2 <string>s; put result in <string>
#include <iostream>
#include <string>

using namespace std;

int main() {
  string s1 = "Hello, ";
  string s2 = "World!";

  // +1 for \0
  string result = s1 + s2;

  // print
  cout << result << endl;

  return 0;
}