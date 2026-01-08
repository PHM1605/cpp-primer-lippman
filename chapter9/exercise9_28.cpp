// Write a function that takes a forward_list<string> and 2 <string>s
// Find 1st <string> in <list>, insert 2nd one after that (insert to the end if not find)
#include <iostream>
#include <forward_list>
#include <string>

using namespace std;

forward_list<string> find_and_insert(forward_list<string> ls, string& searched, string& inserted) {
  auto prev = ls.before_begin();
  auto curr = ls.begin();
  while(curr != ls.end()) {
    // search, found => insert at place
    if (*curr == searched) {
      curr = ls.insert_after(curr, inserted); 
      return ls;
    } else {
      prev = curr;
      curr++;
    }
  }
  // search, not-found => insert at end
  if (curr == ls.end()) {
    ls.insert_after(prev, inserted);
  }
  return ls;
}

void print_forward_list(forward_list<string>& ls) {
  for (auto iter=ls.begin(); iter!=ls.end(); iter++) {
    cout << *iter << endl;
  }
}

int main() {
  forward_list<string> ls = {"This is a test string", "hello", "my name is abc"};
  string found = "hello";
  string not_found = "not found anywhere"; 
  string inserted = "add more information";
  
  cout << "Found string test:\n";
  auto result_found = find_and_insert(ls, found, inserted);
  print_forward_list(result_found);

  cout << "\nNot-found string test:\n";
  auto result_not_found = find_and_insert(ls, not_found, inserted);
  print_forward_list(result_not_found);
  
  return 0;
}