// Write a function that takes a &container and prints its elements
#include <iostream>
#include <list>
#include <vector>

using namespace std;

template<typename Container>
void print_container(const Container& ct) {
  for (auto iter=ct.begin(); iter!=ct.end(); iter++) {
    cout << *iter << " ";
  }
  cout << endl;
}

int main() {
  vector<int> vi {1,2,3};
  list<string> ls {"hello", "world"};

  cout << "Print vector of ints: ";
  print_container(vi);
  cout << "Print list of strings: ";
  print_container(ls);

  return 0;
}