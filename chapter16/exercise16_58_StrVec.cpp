// Write <StrVec> with <emplace_back>
#include <iostream>
#include <memory>

using namespace std;

class StrVec {
public:
  StrVec():
    elements(nullptr), first_free(nullptr), cap(nullptr) {}
  StrVec(const initializer_list<string>); // init-list constructor
  ~StrVec(); // destructor

  void push_back(const string&);
  size_t size() const { return first_free-elements; }
  size_t capacity() const { return cap-elements; }

  string* begin() const { return elements; }
  string* end() const { return first_free; }

  // NEW
  template<class... Args>
  void emplace_back(Args&&... args);

private:
  static allocator<string> alloc;

  string* elements; // 1st element in array
  string* first_free; // one-past-last
  string* cap; // one-past-capacity

  // get more space and copy elements
  void reallocate();
  // alloc when there is no elements
  void chk_n_alloc() { 
    if(size()==capacity()) 
      reallocate(); 
  }
  // copy from a range to a range
  pair<string*, string*> alloc_n_copy(const string*, const string*);
  void free();
};
allocator<string> StrVec::alloc;

void StrVec::reallocate() {
  // every realloc doubles the size; if no size the allocate 1
  auto newcapacity = size() ? 2*size() : 1;
  auto newdata = alloc.allocate(newcapacity);
  // move all elements from old array to new location
  auto dest = newdata; // new
  auto elem = elements; // old
  for (size_t i=0; i!=size(); ++i) {
    alloc.construct(dest++, std::move(*elem++));
  }
  // free old
  free();
  // update current
  elements = newdata;
  first_free = dest;
  cap = elements + newcapacity;
}

void StrVec::push_back(const string& s) {
  chk_n_alloc();
  alloc.construct(first_free++, s);
}

void StrVec::free() {
  if (elements) {
    // moving backward
    for(auto p=first_free; p!=elements; /*empty*/) {
      alloc.destroy(--p);
    }
    alloc.deallocate(elements, cap-elements);
  }
}

pair<string*, string*> StrVec::alloc_n_copy(const string* b, const string* e){
  auto data = alloc.allocate(e-b);
  // copy from beginning-to to a new allocated place
  return {data, uninitialized_copy(b, e, data)};
}

StrVec::StrVec(const initializer_list<string> ils) {
  auto newdata = alloc_n_copy(ils.begin(), ils.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

StrVec::~StrVec() { free(); }

// NEW
template<class... Args>
inline void StrVec::emplace_back(Args&&... args) {
  chk_n_alloc();
  // alloc.construct(<loc>, 5, '!') => "!!!!!"
  alloc.construct(first_free++, std::forward<Args>(args)...);
}

int main() {
  StrVec v {"hello", "world"};
  v.push_back("hi");
  v.emplace_back(5, '!');

  cout << "size: " << v.size() << endl;
  for (auto p=v.begin(); p!=v.end(); ++p) {
    cout << *p << endl;
  }

  return 0;
}