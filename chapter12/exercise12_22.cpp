// Define <ConstStrBlobPtr> to be used with const StrBlob
#include <iostream>
#include <vector>
#include <memory>

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
public:
  ConstStrBlobPtr(const StrBlob& a, size_t sz=0):
    wptr(a.data), curr(sz) {}
  
  const string& deref() const; // NOTE: this is where need a const string
  ConstStrBlobPtr& incr();

private:
  shared_ptr<vector<string>> check(size_t, const string&) const;

  weak_ptr<vector<string>> wptr;
  size_t curr;
};

// StrBlob implimentation
ConstStrBlobPtr StrBlob::begin() const {
  return ConstStrBlobPtr(*this);
}

ConstStrBlobPtr StrBlob::end() const {
  return ConstStrBlobPtr(*this, data->size());
}

// ConstStrBlobPtr implementation
shared_ptr<vector<string>> ConstStrBlobPtr::check(size_t i, const string& msg) const {
  auto ret = wptr.lock();
  if (!ret)
    throw runtime_error("unbound ConstStrBlobPtr");
  if (i>=ret->size())
    throw out_of_range(msg);
  return ret;
}

const string& ConstStrBlobPtr::deref() const {
  auto p = check(curr, "dereference pass end");
  return (*p)[curr];
}

ConstStrBlobPtr& ConstStrBlobPtr::incr() {
  check(curr, "increment pass end");
  ++curr;
  return *this;
}

int main() {
  // show that it works with <const StrBlob>
  const StrBlob blob = {"hello", "const", "world"};
  try {
    for (auto p=blob.begin(); ; p.incr()) {
      cout << p.deref() << endl;
      // p.deref() = "hack"; // this should raises an error because it's CONST
    }
  }
  catch (out_of_range&) {
    cout << "We reach the end() of vector<string>" << endl;
  }
}