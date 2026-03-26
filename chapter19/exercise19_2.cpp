// Write <StrVec> with custom <operator new> and <operator delete>
#include <iostream>
#include <memory>
#include <cstdlib>

using namespace std;

// NOTE: custom global operators
void* operator new(size_t size) {
  cout << "[custom new] allocating " << size << " bytes\n";
  if (void* p = malloc(size))
    return p;
  throw bad_alloc();
}
void operator delete(void* mem) noexcept {
  cout << "[custom delete]\n";
  free(mem);
}
void operator delete(void* mem, size_t size) noexcept {
  cout << "[custom delete] " << size << " bytes\n";
  free(mem);
}

class StrVec {
public:
  StrVec():
    elements(nullptr), first_free(nullptr), cap(nullptr) {}
  StrVec(const StrVec&); // copy constructor
  StrVec(const initializer_list<string>); // constructor with initializer_list
  StrVec& operator=(const StrVec&);
  ~StrVec();

  void push_back(const string&);
  size_t size() const { return first_free-elements; }
  size_t capacity() const { return cap-elements; }
  string* begin() const { return elements; }
  string* end() const { return first_free; }

private:
  string* elements; // pointer to 1st element in array
  string* first_free; // pointer to 1-past-last
  string* cap; // pointer to 1-past-capacity

  static allocator<string> alloc;

  void reallocate(); // get more space and copy existing elements
  // trigger reallocated() when there is no space left
  void chk_n_alloc() {
    if (size() == capacity()) 
      reallocate();
  }
  // copy from a range to a range
  pair<string*, string*> alloc_n_copy(const string*, const string*);
  void free();
};
allocator<string> StrVec::alloc;

void StrVec::push_back(const string& s) {
  chk_n_alloc();
  alloc.construct(first_free++, s);
}

void StrVec::reallocate() {
  // every reallocate we double the size (if no size yet then set at 1)
  auto newcapacity = size() ? 2*size() : 1;
  auto newdata = alloc.allocate(newcapacity);
  // move all elements from old loc to new
  auto dest = newdata;
  auto elem = elements;
  for (size_t i=0; i!=size(); ++i) {
    alloc.construct(dest++, std::move(*elem++));
  }
  // free old loc
  free();
  // update new info
  elements = newdata;
  first_free = dest;
  cap = elements + newcapacity;
}

// allocate just enough to copy
pair<string*, string*> StrVec::alloc_n_copy(const string* b, const string* e) {
  auto data = alloc.allocate(e-b);
  return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free() {
  if (elements) {
    // moving backward
    for (auto p=first_free; p!=elements; /**/) {
      alloc.destroy(--p);
    }
    alloc.deallocate(elements, cap-elements);
  }
}

// copy constructors
StrVec::StrVec(const StrVec& s) {
  auto newdata = alloc_n_copy(s.begin(), s.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

StrVec::StrVec(const initializer_list<string> ils) {
  auto newdata = alloc_n_copy(ils.begin(), ils.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

StrVec& StrVec::operator=(const StrVec& rhs) {
  auto data = alloc_n_copy(rhs.begin(), rhs.end());
  free();
  elements = data.first;
  first_free = cap = data.second;
  return *this;
}

StrVec::~StrVec() {
  free();
}

int main() {
  StrVec v1;
  v1.push_back("a");
  v1.push_back("b");
  cout << "v1 size: " << v1.size() << endl;

  StrVec v2 {"hello", "world", "StrVec"};
  cout << "v2 size: " << v2.size() << endl;

  return 0;
}