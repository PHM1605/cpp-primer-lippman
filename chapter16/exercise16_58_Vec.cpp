// Write <StrVec> with <emplace_back>
#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class Vec {
public:
  Vec():
    elements(nullptr), first_free(nullptr), cap(nullptr) {}
  Vec(const initializer_list<T>); // init-list constructor
  ~Vec(); // destructor

  void push_back(const T&);
  size_t size() const { return first_free-elements; }
  size_t capacity() const { return cap-elements; }

  T* begin() const { return elements; }
  T* end() const { return first_free; }

  // NEW
  template<class... Args>
  void emplace_back(Args&&... args);

private:
  static allocator<T> alloc;

  T* elements; // 1st element in array
  T* first_free; // one-past-last
  T* cap; // one-past-capacity

  // get more space and copy elements
  void reallocate();
  // alloc when there is no elements
  void chk_n_alloc() { 
    if(size()==capacity()) 
      reallocate(); 
  }
  // copy from a range to a range
  pair<T*, T*> alloc_n_copy(const T*, const T*);
  void free();
};
template<typename T>
allocator<T> Vec<T>::alloc;

template<typename T>
void Vec<T>::reallocate() {
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

template<typename T>
void Vec<T>::push_back(const T& val) {
  chk_n_alloc();
  alloc.construct(first_free++, val);
}

template<typename T>
void Vec<T>::free() {
  if (elements) {
    // moving backward
    for(auto p=first_free; p!=elements; /*empty*/) {
      alloc.destroy(--p);
    }
    alloc.deallocate(elements, cap-elements);
  }
}

template<typename T>
pair<T*, T*> Vec<T>::alloc_n_copy(const T* b, const T* e){
  auto data = alloc.allocate(e-b);
  // copy from beginning-to to a new allocated place
  return {data, uninitialized_copy(b, e, data)};
}

template<typename T>
Vec<T>::Vec(const initializer_list<T> ils) {
  auto newdata = alloc_n_copy(ils.begin(), ils.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

template<typename T>
Vec<T>::~Vec() { free(); }

// NEW
template<typename T>
template<class... Args>
inline void Vec<T>::emplace_back(Args&&... args) {
  chk_n_alloc();
  // alloc.construct(<loc>, 5, '!') => "!!!!!"
  alloc.construct(first_free++, std::forward<Args>(args)...);
}

int main() {
  Vec<string> v {"hello", "world"};
  v.push_back("hi");
  v.emplace_back(5, '!');

  cout << "size: " << v.size() << endl;
  for (auto p=v.begin(); p!=v.end(); ++p) {
    cout << *p << endl;
  }

  return 0;
}