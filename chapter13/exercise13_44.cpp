// Write a <String> version that has a default constructor and constructor that takes a pointer to C-style string.
// Use <allocator> to allocate data that the String class use 
#include <iostream>
#include <cstring>
#include <memory>

using namespace std;

class String {
public:
  String();
  String(const char* str);
  ~String();

  char* c_str() { return elements; }
private:
  static allocator<char> alloc;

  char* elements; // pointer to the 1st element
  char * end; // pointer one-past-end

  void free();
};

allocator<char> String::alloc;

String::String(): 
  elements(nullptr), end(nullptr) {}

String::String(const char* str) {
  size_t len = strlen(str) + 1; // mem-length +1 for '\0'
  elements = alloc.allocate(len);
  end = elements+len;

  uninitialized_copy(str, str+len, elements);
}

void String::free() {
  if (elements) {
    for (auto p=end; p!=elements; )
      alloc.destroy(--p);
    alloc.deallocate(elements, end-elements);
  }
}

String::~String() {
  free();
}

int main() {
  String s1;
  String s2("hello allocator");

  cout << s2.c_str() << endl;

  return 0;
}
