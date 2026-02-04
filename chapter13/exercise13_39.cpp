// Write <StrVec> that simulates a vector-of-strings
#include <iostream>

using namespace std;

class StrVec {
public:
  StrVec():
    elements(nullptr), first_free(nullptr), cap(nullptr) {}
  StrVec(const StrVec&); // copy constructor
  StrVec& operator=(const StrVec&); // copy assignment
  ~StrVec(); // destructor

  void push_back(const string&);
  size_t size() const { return first_free - elements; } // #elements in vector
  size_t capacity() const { return cap-elements; } // how big is total capacity
  
  string* begin() const { return elements; }
  string* end() const { return first_free; }

private:
  static allocator<string> alloc;
  string* elements; // pointer to the 1st element in array
  string* first_free; // pointer to one-past-last-constructed
  string* cap; // pointer to one-past-end (ALLOCATED - may or may not constructed) of array

  void reallocate(); // get more space and copy existing elements
  // trigger <reallocate()> when there is no space left
  void check_n_alloc() {
    if (size() == capacity())
      reallocate();
  }

  // use when we "copy" or "assign"
  pair<string*, string*> alloc_n_copy(const string*, const string*);

  void free(); // destroy elements and free space
};

int main() {
  return 0;
}