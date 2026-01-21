// Write a program to read a list of words from <cin> using <allocator>
#include <iostream>
#include <memory>

using namespace std;

int main() {
  size_t n = 42;
  allocator<string> alloc;
  auto p = alloc.allocate(n); // original location
  string word; 
  string* q = p; // running variable; to compare with original to see where we go
  while(cin >> word && q!=p+n)
    alloc.construct(q++, word);
  
  // print 
  for (string* it=p; it != q; ++it) {
    cout << *it << endl;
  }

  return 0;
}