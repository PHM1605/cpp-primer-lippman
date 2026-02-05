// Write <StrVec> that simulates a vector-of-strings
#include <iostream>
#include <memory>

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
  void chk_n_alloc() {
    if (size() == capacity())
      reallocate();
  }

  // use when we "copy" or "assign" from a range of <1st-pointer> - <2nd-pointer>
  pair<string*, string*> alloc_n_copy(const string*, const string*);

  void free(); // destroy elements and free space
};

void StrVec::push_back(const string& s) {
  // make sure there is room for another element
  chk_n_alloc();
  // construct that element
  alloc.construct(first_free++, s);
}

// return range of allocation
pair<string*, string*> StrVec::alloc_n_copy(const string* b, const string* e) {
  // alloc just enough space for range <beginning>-<end>
  auto data = alloc.allocate(e-b); // <data>: pointer to 1st available slot
  // <uninitialized_copy>: copy from <begin> to <end> to <data-location>; return pointer to one-past-last 
  return {data, uninitialized_copy(b, e, data)}; 
}

void StrVec::free() {
  if (elements) {
    // moving backward
    for (auto p=first_free; p!=elements; /*empty*/) {
      alloc.destroy(--p);
    }
    alloc.deallocate(elements, cap-elements);
  }
}

// Copy-control
// Copy constructor
StrVec::StrVec(const StrVec &s) {
  auto newdata = alloc_n_copy(s.begin(), s.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}
// destructor
StrVec::~StrVec() {
  free();
}
// copy assignment (NOTE: don't forget self-assignment)
StrVec& StrVec::operator=(const StrVec& rhs) {
  auto data = alloc_n_copy(rhs.begin(), rhs.end()); // save right-side
  free(); // free left-side
  // get back right-side values
  elements = data.first;
  first_free = cap = data.second;
  return *this;
}

int main() {
  return 0;
}