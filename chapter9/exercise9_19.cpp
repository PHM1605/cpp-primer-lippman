// Write a program to read a sequence of strings from <cin> to <list>
// Use <iterator>s to print elements in <list>
#include <iostream>
#include <string>
#include <list>

using namespace std;

int main() {
  string word;
  list<string> ls;

  // read <cin> to deque
  while(cin >> word) {
    ls.push_back(word);
  }

  // use iterators to print out
  for (auto iter=ls.begin(); iter!=ls.end(); iter++) {
    cout << *iter << endl;
  }

  return 0;
}