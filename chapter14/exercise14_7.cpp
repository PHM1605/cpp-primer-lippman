// Add operator<< for <String> class 
#include <iostream>
#include <cstring>
#include <memory>

using namespace std;

class String {
  friend ostream& operator<<(ostream&, const String&);
public:
  String();
  String(const char*);
  ~String();

private:
  char* elements; // pointer to the 1st element
  char* end; // pointer one-past-end

  static allocator<char> alloc;
  void free();
};
allocator<char> String::alloc;

String::String():
  elements(nullptr), end(nullptr) {}

String::String(const char* str) {
  size_t len = strlen(str) + 1; // +1 for '\0'
  elements = alloc.allocate(len);
  end = elements + len;
  uninitialized_copy(str, str+len, elements);
}

void String::free() {
  if (elements) {
    for (auto p=end; p!=elements; ) {
      alloc.destroy(--p);
    }
    alloc.deallocate(elements, end-elements);
  }
}

String::~String() {
  free();
}

ostream& operator<<(ostream& os, const String& str) {
  os << str.elements;
  return os;
}

int main() {
  String s1("hello allocator");
  cout << s1 << endl;

  return 0;
}