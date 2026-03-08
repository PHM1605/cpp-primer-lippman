// Rewrite <StrVec> to a generic <Vec>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

template<typename T>
class Vec {
public:
  // constructors
  Vec():
    elements(nullptr), first_free(nullptr), cap(nullptr) {}
  Vec(const Vec&);
  Vec(const initializer_list<T>);
  // assignment oprator
  Vec& operator=(const Vec&);
  // destructor
  ~Vec();

  // operators
  void push_back(const T&);
  size_t size() const { return first_free-elements; } 
  size_t capacity() const { return cap-elements; }
  T* begin() const { return elements; }
  T* end() const { return first_free; }
  void reserve(size_t n);

private:
  static allocator<T> alloc;
  T* elements; // pointer to 1st
  T* first_free; // pointer to 1-past-last
  T* cap; // pointer to 1-past-end

  void reallocate(); // get more space and copy existing elements
  void chk_n_alloc() {
    if (size() == capacity())
      reallocate();
  }
  pair<T*,T*> alloc_n_copy(const T*, const T*);
  void free();
};
template<typename T>
allocator<T> Vec<T>::alloc;

template<typename T>
void Vec<T>::reallocate() {
  // every time reallocating we double the size
  auto newcapacity = size() ? 2*size() : 1;
  auto newdata = alloc.allocate(newcapacity);
  // move all elements from old array to new location
  auto dest = newdata; // new
  auto elem = elements; // old
  for (size_t i=0; i!=size(); ++i) {
    alloc.construct(dest++, std::move(*elem++));
  }
  // still, we must free old one
  free();
  // update old object to new location
  elements = newdata;
  first_free = dest;
  cap = elements + newcapacity;
}

template<typename T>
void Vec<T>::push_back(const T& s) {
  chk_n_alloc();
  alloc.construct(first_free++, s);
}

// return range of allocation
template<typename T>
pair<T*,T*> Vec<T>::alloc_n_copy(const T* b, const T* e) {
  auto data = alloc.allocate(e-b); // alloc just enough empty space
  // return {begin, one-past-last}
  return {data, uninitialized_copy(b,e,data)};
}

// allocate <n> elements
template <typename T>
void Vec<T>::reserve(size_t n) {
  if (n<=capacity()) return;
  auto newdata = alloc.allocate(n);
  auto dest = newdata;
  auto elem = elements; // old
  for (size_t i=0; i!=size(); i++) 
    alloc.construct(dest++, std::move(*elem++));
  free();
  // change object values to that new area
  elements = newdata;
  first_free = dest;
  cap = elements + n;
}

template <typename T>
void Vec<T>::free() {
  if (elements) {
    // moving backward
    for(auto p=first_free; p!= elements; /*empty*/) {
      alloc.destroy(--p);
    }
    alloc.deallocate(elements, cap-elements);
  }
}

// constructors
template<typename T>
Vec<T>::Vec(const Vec& s) {
  auto newdata = alloc_n_copy(s.begin(), s.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}
template<typename T>
Vec<T>::Vec(const initializer_list<T> ils) {
  auto newdata = alloc_n_copy(ils.begin(), ils.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}
// copy assigment
template<typename T>
Vec<T>& Vec<T>::operator=(const Vec<T>& rhs) {
  auto data = alloc_n_copy(rhs.begin(), rhs.end());
  free();
  elements = data.first;
  first_free = cap = data.second;
  return *this;
}
// destructor
template<typename T>
Vec<T>::~Vec() {
  free();
}


int main() {
  Vec<string> v;
  v.push_back("a");
  v.push_back("b");
  cout << "v size before reserve: " << v.size() << " capacity: " << v.capacity() << endl;
  v.reserve(10);
  cout << "v size after reserve: " << v.size() << " capacity: " << v.capacity() << endl;
  
  // test initializer_list constructor
  Vec<string> v2 {"hello", "world", "Vec"};
  cout << "v2 size: " << v2.size() << " capacity: " << v2.capacity() << endl;

  return 0;
}