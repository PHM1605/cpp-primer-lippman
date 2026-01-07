// Write a program to copy elements from a list<int> to 2 <deques>
// Even-values elements go to 1 queue and odd-values go to the other
#include <iostream>
#include <list>
#include <deque>

using namespace std;

void print_container(deque<int>& di) {
  for (auto& num: di) {
    cout << num << " ";
  }
  cout << endl;
}

int main() {
  list<int> li {1,5,2,0,6};
  deque<int> di1;
  deque<int> di2;

  // analyze which one is even, which one is odd
  for (auto& item: li) {
    if (item % 2 == 0) {
      di1.push_back(item);
    } else {
      di2.push_back(item);
    }
  }

  // print to check
  print_container(di1);
  print_container(di2);

  return 0;
}