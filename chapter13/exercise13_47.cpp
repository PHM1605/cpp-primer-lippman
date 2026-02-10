// Write our <String> version - with "copy-constructor" and "copy assignment"
// Print every time it is called
// Use "push_back" many times to check
#include <iostream>
#include <cstring>
#include <memory>
#include <vector>

using namespace std;

class String {
public:
  String(); // default constructor
  String(const char*); // constructor from "C-string"
  String(const String&); // copy constructor
  String& operator=(const String&); // copy assigment
  ~String(); // destructor

private:
  static allocator<char> alloc;
  char* elements; // pointer to the 1st element
  char* end; // pointer to one-past-last element

  void free(); // clean all elements
};

allocator<char> String::alloc;

String::String():
  elements(nullptr), end(nullptr) {}

String::String(const char* str) {
  cout << "Use constructor with C-string\n";

  size_t len = strlen(str) + 1; // +1 for '\0'
  elements = alloc.allocate(len);
  end = elements+len;
  uninitialized_copy(str, str+len, elements);
}

String::String(const String& str) {
  cout << "Use copy constructor\n";

  size_t len = str.end - str.elements;
  elements = alloc.allocate(len);
  end = elements + len;
  uninitialized_copy(str.elements, str.end, elements);
}

String& String::operator=(const String& str) {
  cout << "Use assignment operator\n";
  // to prevent self-assigment
  if (this != &str) {
    // step 1: copy StringB's values to new location
    char* newdata = nullptr;
    char* newend = nullptr;
    if (str.elements) {
      auto len = str.end - str.elements;
      newdata = alloc.allocate(len);
      newend = newdata + len;
      uninitialized_copy(str.elements, str.end, newdata);
    } 
    // step 2; free old location of StringA
    free();
    // step 3: give ownership to StringA
    elements = newdata;
    end = newend;
  }
  return *this;
}

void String::free() {
  if (elements) {
    for (auto p = end; p != elements; )
      alloc.destroy(--p);
    alloc.deallocate(elements, end-elements);  
  }
}

String::~String() {
  free();
}

int main() {
  vector<String> v;

  cout << "---- push_back temporary ----\n";
  // 1/ construct <String> from C-string "hello"
  // 2/ copy construct into <vector>
  v.push_back("hello");
  
  // 1/ construct <String> from C-string "world"
  // 2/ copy construct "hello" to a new place (allocate more space)
  // 3/ copy construct "world" to new place
  v.push_back("world");

  return 0;
}