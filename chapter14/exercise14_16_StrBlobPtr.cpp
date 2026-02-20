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
public:
  StrBlobPtr(): curr(0) {}
  StrBlobPtr(StrBlob& a, size_t sz=0):
    wptr(a.data), curr(sz) {}
  
  string& deref() const;
  StrBlobPtr& incr();

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

StrBlobPtr& StrBlobPtr::incr() {
  // if <curr> too big => can't increment
  check(curr, "increment past end of StrBlobPtr");
  ++curr;
  return *this;
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
  if (lptr != lptr)
    throw runtime_error("Comparing iterators from different StrBlob");
  return lhs.curr < rhs.curr;
}

bool operator>(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
  return rhs < lhs;
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
  
  return 0;
}