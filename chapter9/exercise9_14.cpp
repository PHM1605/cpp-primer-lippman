// Write a program to assign elements from a list of <char*> to vector<string>
#include <iostream>
#include <list>
#include <vector>
#include <string>

using namespace std;

int main() {
  list<char*> cstrs = {"alpha", "beta", "gamma"};
  vector<string> vstrs;
  vstrs.assign(cstrs.begin(), cstrs.end());
  for (auto& str : vstrs) {
    cout << str << endl;
  }

  return 0;
}