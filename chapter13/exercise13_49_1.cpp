// Create <StrVec> with "move-constructor" and "move-assignment"
#include <iostream>
#include <memory>

using namespace std;

class StrVec {
public:
  StrVec():
    elements(nullptr), first_free(nullptr), cap(nullptr) {}
  StrVec(const StrVec&); // copy constructor
  StrVec(const initializer_list<string>);
  StrVec& operator=(const StrVec&); // copy assignment
  ~StrVec();

  // NEW: move constructor
  StrVec::StrVec(StrVec &&s) noexcept:
    elements(s.elements), first_free(s.first_free), cap(s.cap)
  {
    // leave <s> in a state that is safe to use destructor
    s.elements = s.first_free = s.cap = nullptr;
  }
  
  size_t size() const { return first_free-elements; }
  size_t capacity() const { return cap-elements; }

  string* begin() const { return elements; }
  string* end() const { return first_free; }

private:
  static allocator<string> alloc;

  string* elements; // pointer to the 1st element in array
  string* first_free; // pointer to one-past-last
  string* cap; // pointer to one-past-capacity

  void reallocate(); // get more space and copy existing elements
  // call reallocate() when there is no space left
  void chk_n_alloc() {
    if (size() == capacity())
      reallocate();
  }
  void free(); // destroy elements and free space 
};

allocator<string> StrVec::alloc;

// Aux functions
void StrVec::free() {
  if (elements) {
    // moving backward
    for (auto p=first_free; p!=elements; /*empty*/) {
      alloc.destroy(--p);
    }
    alloc.deallocate(elements, cap-elements);
  }
}

// Definitions
StrVec::~StrVec() {
  free();
}

int main() {

}