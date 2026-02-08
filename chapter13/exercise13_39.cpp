// Write <StrVec> that simulates a vector-of-strings
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
  ~StrVec(); // destructor

  void push_back(const string&);
  size_t size() const { return first_free - elements; } // #elements in vector
  size_t capacity() const { return cap-elements; } // how big is total capacity
  
  string* begin() const { return elements; }
  string* end() const { return first_free; }

  // some functionalities
  void reserve(size_t n);
  void resize(size_t);
  void resize(size_t, const string&);

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

allocator<string> StrVec::alloc;

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
// Constructor with <initializer_list>
StrVec::StrVec(const initializer_list<string> ils) {
  auto newdata = alloc_n_copy(ils.begin(), ils.end());
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

void StrVec::reallocate() {
  // every time reallocating we double the size; if no size yet then allocate 1
  auto newcapacity = size() ? 2*size() : 1; 
  auto newdata = alloc.allocate(newcapacity);
  
  // move all elements from old array to new location
  auto dest = newdata; // start of new location
  auto elem = elements; // start of old array
  for (size_t i=0; i!=size(); ++i) {
    alloc.construct(dest++, std::move(*elem++)); // NOTE: <move-constructor> here
  }
  // still, we must free the old one
  free();
  // update our old object to point to new elements
  elements = newdata;
  first_free = dest;
  cap = elements + newcapacity;
}

// Some functionalities
// reserve => allocate <n> elements
void StrVec::reserve(size_t n) {
  if (n <= capacity()) 
    return;
  // if <n> too big => allocate completely new area and move data there
  auto newdata = alloc.allocate(n);
  auto dest = newdata;
  auto elem = elements;
  for (size_t i=0; i != size(); i++) {
    alloc.construct(dest++, move(*elem++));
  }
  free();
  // change object values to that new area
  elements = newdata;
  first_free = dest;
  cap = elements + n;
}

// <resize>: if less=>truncate; if more=>append default values
void StrVec::resize(size_t n) {
  resize(n, string());
}
void StrVec::resize(size_t n, const string& s) {
  // destroy extra elements
  if (n<size()) {
    while(first_free != elements+n)
      alloc.destroy(--first_free);
  } else if (n>size()) {
    // allocate if it's too big
    if (n > capacity())
      reserve(n);
    // if bigger but not too big -> construct only
    while (first_free != elements+n)
      alloc.construct(first_free++, s);
  }
}

int main() {
  StrVec v;
  v.push_back("a");
  v.push_back("b");

  v.reserve(10);
  cout << "size: " << v.size() << " capacity: " << v.capacity() << endl;

  v.resize(5, "X");
  cout << "after resize up, size: " << v.size() << endl;

  v.resize(1); // truncate all but the first
  cout << "after resize down, size: " << v.size() << endl;

  // test <initializer_list>
  StrVec v2{"hello", "world", "StrVec"};
  cout << "v2 size: " << v2.size() << " capacity: " << v2.capacity() << endl;

  return 0;
}