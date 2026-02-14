// Create <String> with "move-constructor" and "move-assignment"
#include <iostream>
#include <cstring>
#include <memory>

using namespace std;

class String {
public:
  String(); // default constructor
  String(const char*); // constructor from C-style string
  String(const String&); // copy constructor
  String& operator=(const String&); // copy assignment
  ~String(); // destructor

  // NEW: move constructor
  String(String&&);
  // NEW: move assignment
  String& operator=(String&&);

private:
  char* elements; // pointer to the 1st element
  char* end; // pointer to one-past-last

  void free(); // clean all elements

  static allocator<char> alloc;
};

allocator<char> String::alloc;

// Default constructor
String::String():
  elements(nullptr), end(nullptr) {
  cout << "Use default constructor\n";
}

// Constructor from C-style string
String::String(const char* str) {
  cout << "Use constructor from C-style string\n";
  size_t len = strlen(str) + 1; // +1 for '\0'
  elements = alloc.allocate(len);
  end = elements + len;
  uninitialized_copy(str, str+len, elements);
}

// Copy constructor
String::String(const String& str) {
  cout << "Use copy constructor\n";
  size_t len = str.end - str.elements;
  elements = alloc.allocate(len);
  end = elements + len;
  uninitialized_copy(str.elements, str.end, elements);
}

// Copy assignment
String& String::operator=(const String& str) {
  cout << "Use assignment operator\n";
  // to prevent self-assignment
  if (this != &str) {
    char* newdata = nullptr;
    char* newend = nullptr;
    if (str.elements) {
      auto len = str.end - str.elements;
      newdata = alloc.allocate(len);
      newend = newdata + len;
      uninitialized_copy(str.elements, str.end, newdata);
    }
    free();

    elements = newdata;
    end = newend;
  }
  return *this;
}

// Destructor
String::~String() {
  free();
}

void String::free() {
  if (elements) {
    for (auto p = end; p != elements; /*empty*/) 
      alloc.destroy(--p);
    alloc.deallocate(elements, end-elements);
  }
}

int main() {
  cout << "=== Move Constructor Test ===\n";
  String a("hello");
  String b(std::move(a));

  cout << "=== Move Assignment Test ===\n";
  String c("world");
  String d;
  d = std::move(c);

  cout << "=== Move constructor test ===\n";
  String e = String("temporary");

  return 0;

}