// Extend <StrVec> that simulates a vector-of-strings WITH operator== and operator!=
#include <iostream>
#include <memory>

using namespace std;

class StrVec {
  friend bool operator==(const StrVec&, const StrVec&);
  friend bool operator<(const StrVec&, const StrVec&);
  friend ostream& operator<<(ostream&, const StrVec&);
  
public:
  StrVec():
    elements(nullptr), first_free(nullptr), cap(nullptr) {}
  StrVec(const initializer_list<string>); 
  StrVec(const StrVec&); // Copy constructor
  StrVec& operator=(const StrVec&); // Copy assignment
  ~StrVec(); // destructor

  StrVec& operator=(initializer_list<string>);
  // 2 subscript operators
  string& operator[](size_t n) { return elements[n]; }
  const string& operator[](size_t n) const { return elements[n]; }

  void push_back(const string&);
  size_t size() const { return first_free - elements; }
  size_t capacity() const { return cap - elements; }

private:
  string* elements; // pointer to 1st 
  string* first_free; // pointer to one-past-last
  string* cap; // pointer to one-past-allocated

  static allocator<string> alloc;

  // // copy and assign from a range of 2 pointers
  pair<string*, string*> alloc_n_copy(const string*, const string*);
  void chk_n_alloc();
  
  void reallocate();
  void free(); // destroy elements and free space
};

allocator<string> StrVec::alloc;

StrVec::StrVec(const initializer_list<string> ils) {
  auto newdata = alloc_n_copy(ils.begin(), ils.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

StrVec::StrVec(const StrVec& other) {
  auto data = alloc_n_copy(other.elements, other.first_free);
  elements = data.first;
  first_free = cap = data.second;
}

StrVec& StrVec::operator=(const StrVec& rhs) {
  auto data = alloc_n_copy(rhs.elements, rhs.first_free);
  free(); // free the old memory of <this>
  elements = data.first;
  first_free = cap = data.second;
  return *this;
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
ostream& operator<<(ostream& os, const StrVec& vec) {
  os << "[";
  for (size_t i=0; i<vec.size(); ++i) {
    os << vec.elements[i];
    if (i+1 != vec.size())
      os << ", ";
  }
  os << "]";
  return os;
}
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

StrVec& StrVec::operator=(initializer_list<string> il) {
  cout << "initializer_list assignment!\n";
  auto data = alloc_n_copy(il.begin(), il.end());
  free();
  elements = data.first;
  first_free = cap = data.second;
  return *this;
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

  cout << "=== Test initializer_list assignment operator ===\n";
  StrVec v5;
  v5 = {"this", "is", "a", "sentence"};

  cout << "=== Test [] operators (const and non-const) ===\n";
  const StrVec cvec = v5;
  v5[0] = "THIS";
  cout << v5 << endl;
  // cvec[0] = "abc"; // ERROR
  cout << "Try accessing const element: " << cvec[0] << endl;

  return 0;
}