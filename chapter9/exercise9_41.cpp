// Write a program that initialize a <string> from a vector<char>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<char> vc = {'H','e','l','l','o','W','o','r','l','d'};
  string str(&vc[0]);
  
  cout << str << endl;

  return 0;
}