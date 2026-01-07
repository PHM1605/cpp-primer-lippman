// Write a program to read a sequence of strings from <cin> to <deque>
// Use <iterator>s to print elements in <deque>
#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main() {
  string word;
  deque<string> ds;

  // read <cin> to deque
  while(cin >> word) {
    ds.push_back(word);
  }

  // use iterators to print out
  for (auto iter=ds.begin(); iter!=ds.end(); iter++) {
    cout << *iter << endl;
  }

  return 0;
}