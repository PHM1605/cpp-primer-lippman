// Create <StrVec> with "move-constructor" and "move-assignment"
#include <iostream>
#include <memory>

using namespace std;

class StrVec {
public:
  StrVec():
    elements(nullptr), first_free(nullptr), cap(nullptr) {}
  StrVec(const StrVec&); // copy constructor
  StrVec(const initializer_list<string>); // constructor from list
  StrVec& operator=(const StrVec&); // copy assignment
  ~StrVec();

  // NEW: move constructor
  StrVec(StrVec &&s) noexcept;
  StrVec& operator=(StrVec&& rhs) noexcept; 
  
  size_t size() const { return first_free-elements; }
  size_t capacity() const { return cap-elements; }

  string* begin() const { return elements; }
  string* end() const { return first_free; }

  void push_back(const string&);

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
  // return <pair> of iterators of the destination
  pair<string*, string*> alloc_n_copy(const string*, const string*);

  void free(); // destroy elements and free space 
};
allocator<string> StrVec::alloc;

// Copy constructor
StrVec::StrVec(const StrVec& s) {
  cout << "COPY CONSTRUCTOR\n";
  auto newdata = alloc_n_copy(s.begin(), s.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

// Constructor with list
StrVec::StrVec(const initializer_list<string> ils) {
  auto newdata = alloc_n_copy(ils.begin(), ils.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

// Copy assignment
StrVec& StrVec::operator=(const StrVec& rhs) {
  cout << "COPY ASSIGNMENT\n";
  auto data = alloc_n_copy(rhs.begin(), rhs.end());
  free(); // free left side
  elements = data.first;
  first_free = cap = data.second;
  return *this;
}

// Destructor
StrVec::~StrVec() {
  free();
}

// Move constructor
StrVec::StrVec(StrVec &&s) noexcept:
  elements(s.elements), first_free(s.first_free), cap(s.cap){
  cout << "MOVE CONSTRUCTOR\n";
  // leave <s> in a state that is safe to use destructor
  s.elements = s.first_free = s.cap = nullptr;
}

// Move assignment
StrVec& StrVec::operator=(StrVec&& rhs) noexcept {
  cout << "MOVE ASSIGNMENT\n";
  // direct test for self-assignment
  if (this != &rhs) {
    free();
    elements = rhs.elements;
    first_free = rhs.first_free;
    cap = rhs.cap;
    // leave rhs in destructible state
    rhs.elements = rhs.first_free = rhs.cap = nullptr;
  }
  return *this;
}

void StrVec::reallocate() {
  cout << "REALLOCATE\n"; 
  // every time reallocating we double the size
  // if no size yet then allocate 1
  auto newcapacity = size() ? 2*size() : 1;
  auto first = alloc.allocate(newcapacity);

  // MOVE all elements from old array to new location with MOVE iterators
  auto last = uninitialized_copy(
    make_move_iterator(begin()),
    make_move_iterator(end()),
    first
  );

  // still, we must clean the old ones
  free();
  // update current object info
  elements = first;
  first_free = last;
  cap = elements + newcapacity;
}

// return iterators of destination
pair<string*, string*> StrVec::alloc_n_copy(const string* b, const string* e) {
  auto data = alloc.allocate(e-b);
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

void StrVec::push_back(const string& s) {
  chk_n_alloc();
  alloc.construct(first_free++, s);
}

int main() {
  cout << "\n--- Test 1: Move constructor ---\n";
  StrVec v1; 
  StrVec v2 = std::move(v1);

  cout << "\n--- Test 2: Move assignment ---\n";
  StrVec v3;
  StrVec v4;
  v4 = std::move(v3);

  cout << "\n--- Test reallocate ---\n";
  StrVec v;
  v.push_back("one"); // capacity 0->1 (REALLOC)
  v.push_back("two"); // capacity 1->2 (REALLOC)
  v.push_back("three"); // capacity 2->4 (REALLOC)
  v.push_back("four"); // NO REALLOC
  v.push_back("five"); // capacity 4->8 (REALLOC)

  return 0;
}