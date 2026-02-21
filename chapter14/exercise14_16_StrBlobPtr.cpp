// Extend <StrBlobStr> to have operator== and operator!=
// <StrBlobStr> throws an exception on attempts to access a nonexistent element
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// Original <StrBlob>
class StrBlob {
  friend bool operator==(const StrBlob&, const StrBlob&);
  friend bool operator!=(const StrBlob&, const StrBlob&);
  friend class StrBlobPtr;
public:
  StrBlob();
  StrBlob(initializer_list<string> il);

private:
  shared_ptr<vector<string>> data;
};

StrBlob::StrBlob():
  data(make_shared<vector<string>>()) {}

StrBlob::StrBlob(initializer_list<string> il):
  data(make_shared<vector<string>>(il)) {}

bool operator==(const StrBlob& a, const StrBlob& b) {
  return *a.data == *b.data;
}

bool operator!=(const StrBlob& a, const StrBlob& b) {
  return !(a==b);
}

// Additional <StrBlobStr> to check access
class StrBlobPtr {
  friend bool operator==(const StrBlobPtr&, const StrBlobPtr&);
  friend bool operator!=(const StrBlobPtr&, const StrBlobPtr&);
  friend bool operator<(const StrBlobPtr&, const StrBlobPtr&);
  friend ptrdiff_t operator-(const StrBlobPtr&, const StrBlobPtr&);

public:
  StrBlobPtr(): curr(0) {}
  StrBlobPtr(StrBlob& a, size_t sz=0):
    wptr(a.data), curr(sz) {}
  
  string& deref() const;
  // Subscript operator
  string& operator[](size_t);
  // Prefix operators
  StrBlobPtr& operator++();
  StrBlobPtr& operator--();
  // Postfix operators => return COPY OF THE OLD ELEMENT
  StrBlobPtr operator++(int);
  StrBlobPtr operator--(int);
  // Arithmetic operator
  StrBlobPtr& operator+=(size_t);
  StrBlobPtr& operator-=(size_t);
  StrBlobPtr operator+(size_t);
  StrBlobPtr operator-(size_t);

private:
  size_t curr; // current position within array
  // weak pointer to data vector
  weak_ptr<vector<string>> wptr;
  // return a pointer to data-vector if check succeeds
  shared_ptr<vector<string>> check(size_t, const string&) const;
};

shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string& msg) const {
  auto ret = wptr.lock(); // return <shared_ptr> if object exists, else raise error
  if (!ret) 
    throw runtime_error("unbound StrBlobPtr");
  if (i >= ret->size())
    throw out_of_range(msg);
  return ret;
}

string& StrBlobPtr::deref() const {
  auto p = check(curr, "derefernce past end");
  return (*p)[curr];
}

bool operator==(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
  return lhs.curr == rhs.curr && lhs.wptr.lock() == rhs.wptr.lock();
}

bool operator!=(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
  return !(lhs == rhs);
}

// Compare only when 2 pointers to the SAME vector and compare its <curr> location
bool operator<(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
  auto lptr = lhs.wptr.lock();
  auto rptr = rhs.wptr.lock();
  // don't compare if 2 data-pool aren't the same
  if (lptr != rptr)
    throw runtime_error("Comparing iterators from different StrBlob");
  return lhs.curr < rhs.curr;
}

bool operator>(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
  return rhs < lhs;
}

string& StrBlobPtr::operator[](size_t n) {
  auto p = check(curr+n, "subscript out of range");
  return (*p)[curr+n];
}

// Prefix operators
StrBlobPtr& StrBlobPtr::operator++() {
  // if <curr> at '\0' then it's error
  check(curr, "increment past end of StrBlobPtr");
  ++curr;
  return *this;
}
StrBlobPtr& StrBlobPtr::operator--() {
  --curr;
  check(curr, "decrement past begin of StrBlobPtr");
  return *this;
}

// Postfix operators => NOTE: we do NOT need check(), which will be handled by prefix version
StrBlobPtr StrBlobPtr::operator++(int) {
  StrBlobPtr ret = *this; // store old value first
  ++*this; // check() already here
  return ret;
}
StrBlobPtr StrBlobPtr::operator--(int) {
  StrBlobPtr ret = *this;
  --*this;
  return ret;
}

// Arithmetic operators + and -
StrBlobPtr StrBlobPtr::operator+(size_t n) {
  StrBlobPtr ret = *this;
  ret += n;
  return ret;
}

StrBlobPtr StrBlobPtr::operator-(size_t n) {
  StrBlobPtr ret = *this;
  ret -= n;
  return ret;
}

// Difference between 2 iterators
ptrdiff_t operator-(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
  auto lptr = lhs.wptr.lock();
  auto rptr = rhs.wptr.lock();
  if (lptr!=rptr)
    throw runtime_error("Subtracting iterators from different StrBlob");
  return static_cast<ptrdiff_t>(lhs.curr) - static_cast<ptrdiff_t>(rhs.curr);
}

int main() {
  cout << "=== Test StrBlobPtr == and != ===\n";
  StrBlob blob({"one", "two", "three"});
  StrBlobPtr p1(blob);
  StrBlobPtr p2(blob);
  StrBlobPtr p3(blob, 1); // with location != 0
  cout << "p1 == p2 ? " << (p1==p2) << endl;
  cout << "p1 != p2 ? " << (p1!=p2) << endl;
  cout << "p1 == p3 ? " << (p1 == p3) << endl;
  cout << "p1 != p3 ? " << (p1 != p3) << endl;

  cout << "Test different blob\n";
  StrBlob blob2({"one", "two", "three"});
  StrBlobPtr p4(blob2);
  cout << "p1 == p4 ? " << (p1==p4) << endl;

  cout << "=== Test StrBlobPtr < and > ===\n";
  StrBlobPtr p5(blob, 2); // point to latter element
  cout << "p3<p5 ? " << (p3<p5) << endl; // true
  cout << "p5>p1 ? " << (p5>p1) << endl; // true

  cout << "\n=== Test operator[] ===\n";
  p1[0] = "ONE";
  cout << "p1[0] = " << p1[0] << endl;

  cout << "\n=== Test ++ and -- ===\n";
  StrBlobPtr old = p1++;
  cout << "Old value before ++: " << old.deref() << endl;
  cout << "New value after --: " << p1.deref() << endl;
  StrBlobPtr old2 = p1--;
  cout << "Old value before --: " << old2.deref() << endl;
  cout << "New value after --: " << p1.deref() << endl;

  cout << "\n=== Test arithmetic operator + and - ===\n";

  cout << "\n=== Test pointer different operator ===\n";

  
  return 0;
}