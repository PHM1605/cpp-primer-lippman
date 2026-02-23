// Define a class that holds a pointer to <StrBlobPtr>; define its overloaded => operator
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class StrBlobPtr;

class StrBlob {
  friend class StrBlobPtr;

public:
  StrBlob(initializer_list<string> il):
    data(make_shared<vector<string>>(il)) {}
  StrBlobPtr begin();
  StrBlobPtr end();

private:
  shared_ptr<vector<string>> data;
};

class StrBlobPtr {
public:
  StrBlobPtr(StrBlob& a, size_t sz=0):
    wptr(a.data), curr(sz) {}
  // member access
  string& operator*() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
  }
  string* operator->() const {
    return & this->operator*();
  }  
  
private:
  shared_ptr<vector<string>> check(size_t i, const string& msg) const {
    auto sp = wptr.lock();
    if (!sp) {
      throw runtime_error("unbound StrBlobPtr");
    }
    if (i>=sp->size())
      throw out_of_range(msg);
    return sp;
  }
  size_t curr;
  weak_ptr<vector<string>> wptr;
};

// ===== StrBlob =====
StrBlobPtr StrBlob::begin() {
  return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end() {
  return StrBlobPtr(*this, data->size());
}

// NEW: wrapper that contains pointer to StrBlobPtr
class BlobPtrWrapper {
public:
  BlobPtrWrapper(StrBlobPtr* p):
    ptr(p) {}
  // Overloaded arrow operator
  StrBlobPtr* operator->() const {
    return ptr;
  }
private:
  StrBlobPtr* ptr;
};

int main() {
  StrBlob blob = {"hello", "world", "Cpp"};
  StrBlobPtr sp = blob.begin();
  BlobPtrWrapper wrapper(&sp);

  cout << wrapper->operator->()->size() << endl; // = string.size()

  return 0;
}