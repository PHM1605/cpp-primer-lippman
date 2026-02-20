// Write a <String> version with operator== and operator!=
#include <iostream>
#include <cstring>
#include <memory>

using namespace std;

class String {
  friend ostream& operator<<(ostream&, const String&);
  friend bool operator==(const String&, const String&);
  friend bool operator!=(const String&, const String&);
  friend bool operator<(const String&, const String&);
  
public:
  String();
  String(const char* str);
  ~String();

private:
  static allocator<char> alloc;

  char* elements; // pointer to the 1st element
  char* end; // pointer one-past-end

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

String::~String() {
  free();
}

void String::free() {
  if (elements) {
    for (auto p=end; p!=elements; ) {
      alloc.destroy(--p);
    } 
    alloc.deallocate(elements, end-elements);
  }
}

ostream& operator<<(ostream& os, const String& str) {
  os << str.elements;
  return os;
}

// NEW
bool operator==(const String& lhs, const String& rhs) {
  return strcmp(lhs.elements, rhs.elements) == 0;
}

bool operator!=(const String& lhs, const String& rhs) {
  return !(lhs == rhs);
}

bool operator<(const String& lhs, const String& rhs) {
  return strcmp(lhs.elements, rhs.elements) < 0;
}

bool operator>(const String& lhs, const String& rhs) {
  return rhs<lhs;
}

int main() {
  String s1("hello world!");
  String s2("hello");
  String s3("hello world!");

  cout << "s1==s2 ? " << (s1==s2) << endl;
  cout << "s1==s3 ? " << (s1==s3) << endl;
  cout << "s1!=s2 ? " << (s1!=s2) << endl;
  cout << "s1!=s3 ? " << (s1!=s3) << endl;

  cout << "=== Test < and > ===\n";
  cout << "s1<s2 ? " << (s1<s2) << endl; // false
  cout << "s1>s2 ? " << (s1>s2) << endl; // true

  return 0;
}