// Extend <StrVec> that simulates a vector-of-strings WITH operator== and operator!=
#include <iostream>
#include <memory>

using namespace std;

class StrVec {
  friend bool operator==(const StrVec&, const StrVec&);
  friend bool operator<(const StrVec&, const StrVec&);
public:
  StrVec():
    elements(nullptr), first_free(nullptr), cap(nullptr) {}
  StrVec(const initializer_list<string>); 
  ~StrVec(); // destructor

  void push_back(const string&);

private:
  string* elements; // pointer to 1st 
  string* first_free; // pointer to one-past-last
  string* cap; // pointer to one-past-allocated

  static allocator<string> alloc;

  // // copy and assign from a range of 2 pointers
  pair<string*, string*> alloc_n_copy(const string*, const string*);
  void chk_n_alloc();
  size_t size() const { return first_free - elements; }
  size_t capacity() const { return cap - elements; }
  void reallocate();
  void free(); // destroy elements and free space
};

allocator<string> StrVec::alloc;

StrVec::StrVec(const initializer_list<string> ils) {
  auto newdata = alloc_n_copy(ils.begin(), ils.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

StrVec::~StrVec() {
  free();
}

// alloc just enough; return range of allocation
pair<string*, string*> StrVec::alloc_n_copy(const string* b, const string* e) {
  auto data = alloc.allocate(e-b);
  return {data, uninitialized_copy(b, e, data)};
}

void StrVec::push_back(const string& s) {
  // make sure there is room for another element
  chk_n_alloc();
  alloc.construct(first_free++, s);
}

void StrVec::chk_n_alloc() {
  if (size() == capacity())
    reallocate();
}

void StrVec::reallocate() {
  // every time reallocating we double the size OR 1 if not yet exists
  auto newcapacity = size() ? 2*size() : 1;
  auto newdata = alloc.allocate(newcapacity);
  // move all elements from old to new location
  auto dest = newdata; // new location
  auto elem = elements; // old location
  for (size_t i=0; i!=size(); i++) {
    alloc.construct(dest++, std::move(*elem++));
  }
  // even if we <move>, still clean up
  free(); 
  // update current location
  elements = newdata;
  first_free = dest;
  cap = elements + newcapacity;
}

void StrVec::free() {
  if (elements) {
    // moving backward
    for (auto p=first_free; p!=elements; ) {
      alloc.destroy(--p);
    }
    alloc.deallocate(elements, cap-elements);
  }
}

// NEW
bool operator==(const StrVec& lhs, const StrVec& rhs) {
  // check same size or not
  if (lhs.size() != rhs.size()) 
    return false;
  // check each element
  for (size_t i=0; i!=lhs.size(); ++i) {
    if (lhs.elements[i] != rhs.elements[i])
      return false;
  }
  return true;
}

bool operator!=(const StrVec& lhs, const StrVec& rhs) {
  return !(lhs == rhs);
}

bool operator<(const StrVec& lhs, const StrVec& rhs) {
  // compare up to the shorter length between the two
  size_t min_size = lhs.size()<rhs.size() ? lhs.size() : rhs.size();
  for (size_t i=0; i<min_size; ++i) {
    if (lhs.elements[i] < rhs.elements[i])
      return true;
    if (rhs.elements[i] < lhs.elements[i])
      return false;
  }
  // If first elements are the same, shorter one in length will be the smaller
  return lhs.size() < rhs.size();
}

bool operator>(const StrVec& lhs, const StrVec& rhs) {
  return rhs<lhs;
}

int main() {
  StrVec v1 {"hello", "world", "StrVec"};
  StrVec v2 {"hello", "world"};
  StrVec v3 {"hello", "world"};
  
  cout << "v1==v2 ? " << (v1==v2) << endl;
  cout << "v2==v3 ? " << (v2==v3) << endl;
  cout << "v1!=v2 ? " << (v1!=v2) << endl;
  cout << "v2!=v3 ? " << (v2!=v3) << endl;

  StrVec v4 {"hello", "me"};
  cout << "=== Test < and > ===\n";
  cout << "v1>v2 ? " << (v1>v2) << endl; // true
  cout << "v4<v2 ? " << (v2<v1) << endl; // true

  return 0;
}