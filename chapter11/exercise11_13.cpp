// Show 3 ways to create a <pair>
#include <iostream>
#include <utility>
#include <string>

using namespace std;

void print_pair(pair<string,int>& p) {
  cout << p.first << ": " << p.second << endl;
}

int main() {
  // method 1: constructor with 2 parameters
  pair<string,int> p1("apple", 1);
  print_pair(p1);

  // method 2: constructor with initializer list
  pair<string,int> p2 = {"banana", 3};
  print_pair(p2);

  // method 3: use <make_pair>
  pair<string, int> p3 = make_pair("orange", 2);
  print_pair(p3);

  return 0;
}