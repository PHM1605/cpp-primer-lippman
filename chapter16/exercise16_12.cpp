// Define generic <Blob> and <BlobPtr> classes
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// forward declaration for "friend"
template<typename> class BlobPtr;
template<typename> class Blob;
template<typename T> bool operator==(const Blob<T>&, const Blob<T>&);

template<typename T>
class Blob {
  // friend declaration
  friend class BlobPtr<T>;
  friend bool operator==<T>(const Blob<T>&, const Blob<T>&);

public:
  typedef T value_type;
  typedef typename vector<T>::size_type size_type; // NOTE: for generic we must say "vector<T>::size_type IS A type" by typing "typename"
  // constructors
  Blob();
  Blob(initializer_list<T> il);
  // number of elements
  size_type size() const { return data->size(); }
  bool empty() const { return data->empty(); }
  // add and remove element
  void push_back(const T& t) { data->push_back(t); }
  void push_back(T&& t) { data->push_back(std::move(t)); }
  void pop_back();
  // element access 
  T& back();
  const T& back() const;
  T& operator[](size_type i);
  const T& operator[](size_type i) const; 

private:
  shared_ptr<vector<T>> data;
  // check if element access is valid
  void check(size_type i, const string& msg) const;
};

// <BlobPtr> throws an exception on attempts to access non-existent element
template <typename T> 
class BlobPtr {
public:
  BlobPtr(): curr(0) {}
  BlobPtr(Blob<T>& a, size_t sz=0):
    wptr(a.data), curr(sz) {}
  // dereference with error checking
  T& operator*() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
  }

  // increment and decrement
  BlobPtr& operator++(); // prefix operator => return updated value
  BlobPtr operator++(int); // postfix => return copy of old value
  BlobPtr& operator--();
  BlobPtr operator--(int);

private:
  size_t curr; // current position within array
  weak_ptr<vector<T>> wptr; // weakly points to underlying vector
  // to check accessing an element is valid
  shared_ptr<vector<T>> check(size_t, const string&) const;
};

template<typename T>
void Blob<T>::check(size_type i, const string& msg) const {
  if (i>=data->size())
    throw out_of_range(msg);
}

template<typename T>
T& Blob<T>::back() {
  check(0, "back on empty Blob");
  return data->back();
}
template<typename T>
const T& Blob<T>::back() const {
  check(0, "back on empty Blob");
  return data->back();
}

template<typename T>
T& Blob<T>::operator[](size_type i) {
  check(i, "subcript out of range");
  return (*data)[i];
}
template<typename T>
const T& Blob<T>::operator[](size_type i) const {
  check(i, "subscript out of range");
  return (*data[i]);
}

template<typename T>
void Blob<T>::pop_back() {
  check(0, "pop_back on empty Blob");
  data->pop_back();
}

// Constructors
template<typename T>
Blob<T>::Blob(): 
  data(make_shared<vector<T>>()) {}

template<typename T>
Blob<T>::Blob(initializer_list<T> il):
  data(make_shared<vector<T>>(il)) {}

template<typename T>
shared_ptr<vector<T>> BlobPtr<T>::check(size_t i, const string& msg) const {
  auto ret = wptr.lock();
  if (!ret)
    throw runtime_error("unbound BlobPtr");
  if (i>=ret->size())
    throw out_of_range(msg);
  return ret;
}

// Prefix increment
template<typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {
  check(curr, "increment past end of BlobPtr");
  ++curr;
  return *this;
}
// Postfix increment
template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int) {
  BlobPtr ret = *this;
  ++*this;
  return ret;
}
// Prefix decrement
template<typename T>
BlobPtr<T>& BlobPtr<T>::operator--() {
  --curr;
  check(curr, "decrement past begin of BlobPtr");
  return *this;
}
// Postfix decrement
template<typename T>
BlobPtr<T> BlobPtr<T>::operator--(int) {
  BlobPtr ret = *this;
  --*this;
  return ret;
}

// friend equality
template<typename T>
bool operator==(const Blob<T>& lhs, const Blob<T>& rhs) {
  return *lhs.data == *rhs.data;
}

int main() {
  Blob<int> b{1,2,3,4};
  cout << "Blob size: " << b.size() << endl;
  cout << "Last element: " << b.back() << endl;
  b.push_back(5);
  cout << "After push_back, last element: " << b.back() << endl;
  cout << "Element at index 2: " << b[2] << endl;

  // Test BlobPtr
  BlobPtr<int> p(b);
  cout << "BlobPtr dereference: " << *p << endl;
  ++p;
  cout << "After ++p: " << *p << endl;
  p++;
  cout << "After p++: " << *p << endl;
  // Test equality
  Blob<int> b2{1,2,3,4,5};
  if (b==b2)
    cout << "b and b2 are equal\n";
  else 
    cout << "b and b2 are NOT equal\n";
    
  return 0;
}