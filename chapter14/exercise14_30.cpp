// Extend <ConstStrBlobPtr> class to have "Member-access operators"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class ConstStrBlobPtr;

class StrBlob {
  friend class ConstStrBlobPtr;

public:
  StrBlob(initializer_list<string> il):
    data(make_shared<vector<string>>(il)) {}

    ConstStrBlobPtr begin() const;
    ConstStrBlobPtr end() const;

private:
  shared_ptr<vector<string>> data;
};

class ConstStrBlobPtr {
  friend bool operator==(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
  friend bool operator!=(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
public:
  ConstStrBlobPtr(const StrBlob& a, size_t sz=0):
    wptr(a.data), curr(sz) {}

    // prefix operators
    ConstStrBlobPtr& operator++();
    ConstStrBlobPtr& operator--();
    // postfix operators
    ConstStrBlobPtr operator++(int); // postfix must return the OLD state
    ConstStrBlobPtr operator--(int);
    // Member access operators
    const string& operator*() const;
    const string* operator->() const;

private:
  shared_ptr<vector<string>> check(size_t, const string&) const;

  weak_ptr<vector<string>> wptr;
  size_t curr; 
};

// ===== StrBlob definitions =====
ConstStrBlobPtr StrBlob::begin() const {
  return ConstStrBlobPtr(*this);
}
ConstStrBlobPtr StrBlob::end() const {
  return ConstStrBlobPtr(*this, data->size());
}

// ===== ConstStrBlobPtr =====
shared_ptr<vector<string>> ConstStrBlobPtr::check(size_t i, const string& msg) const {
  auto sp = wptr.lock();
  if (!sp)
    throw runtime_error("unbound ConstStrBlobPtr");
  if (i>=sp->size())
    throw out_of_range(msg);
  return sp;
}

// prefix ++
ConstStrBlobPtr& ConstStrBlobPtr::operator++() {
  check(curr, "increment past end");
  ++curr;
  return *this;
}
// postfix ++
ConstStrBlobPtr ConstStrBlobPtr::operator++(int) {
  ConstStrBlobPtr ret = *this;
  ++*this;
  return ret;
}

// prefix --
ConstStrBlobPtr& ConstStrBlobPtr::operator--() {
  --curr;
  check(curr, "decrement past begin");
  return *this;
}
// postfix --
ConstStrBlobPtr ConstStrBlobPtr::operator--(int) {
  ConstStrBlobPtr ret = *this;
  --*this;
  return *this;
}

const string& ConstStrBlobPtr::operator*() const {
  auto p = check(curr, "dereference past end");
  return (*p)[curr];
}
const string* ConstStrBlobPtr::operator->() const {
  return & this->operator*();
}

// ===== Outside functions =====
bool operator==(const ConstStrBlobPtr& lhs, const ConstStrBlobPtr& rhs) {
  auto lptr = lhs.wptr.lock();
  auto rptr = rhs.wptr.lock();
  return lptr == rptr && lhs.curr==rhs.curr;
}
bool operator!=(const ConstStrBlobPtr& lhs, const ConstStrBlobPtr& rhs) {
  return !(lhs==rhs);
}

int main() {
  const StrBlob blob = {"hello", "const", "world"};
  for (auto it=blob.begin(); it!=blob.end(); it++) {
    cout << *it << " ";
  }
  cout << "\n";

  // Try using operator ->
  auto it = blob.begin();
  cout << it->size() << "\n";

  return 0;
}