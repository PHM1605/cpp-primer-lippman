// Write a program to read input file one line at a time to <StrBlob>
// Use <StrBlobPtr> to print each element
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>

using namespace std;

class StrBlobPtr;

// ============= ORIGINAL StrBlob =============
class StrBlob {
// to let <StrBlobPtr> access private <data>
friend class StrBlobPtr;

public:
  StrBlob(): data(make_shared<vector<string>>()) {}
  StrBlob(initializer_list<string> il): data(make_shared<vector<string>>(il)) {}

  size_t size() const { return data->size(); }
  bool empty() const { return data->empty(); }
  void push_back(const string& t) { data->push_back(t); }
  void pop_back() {
    data->pop_back();
  }

  // To give <StrBlob> access to it's smart pointer
  StrBlobPtr begin();
  StrBlobPtr end();

private:
  shared_ptr<vector<string>> data;
};
// --------------------------------------------

// ============== Hanlder of StrBlob's pointer ==============
class StrBlobPtr {
public:
  StrBlobPtr(): curr(0) {}
  StrBlobPtr(StrBlob& a, size_t sz=0):
    wptr(a.data), curr(sz) {}
  // check if it's safe to use <vector<string>>
  string& deref() const;
  StrBlobPtr& incr();

private:
  // returns a pointer to data-vector if check succeeds 
  shared_ptr<vector<string>> check(size_t, const string&) const;
  // weak pointer to data-vector
  weak_ptr<vector<string>> wptr;
  size_t curr; // current position within array
};
// ----------------------------------------------------------

StrBlobPtr StrBlob::begin() {
  return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end() {
  return StrBlobPtr(*this, data->size());
}

shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string& msg) const {
  auto ret = wptr.lock(); // return the <shared_ptr> if object exists; other wise <nullptr>
  if (!ret) 
    throw runtime_error("unbound StrBlobPtr");
  if (i>=ret->size()) 
    throw out_of_range(msg);
  return ret;
}

string& StrBlobPtr::deref() const {
  // <p>: shared_ptr
  auto p = check(curr, "dereference past end");
  return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr() {
  // if <curr> past the end => cannot increment it
  check(curr, "increment past end of StrBlobPtr");
  ++curr;
  return *this;
}

int main() {
  fstream fs ("exercise12_20_input.txt");
  auto str_blob = StrBlob();
  string line;
  while (getline(fs, line)) {
    str_blob.push_back(line);
  }

  // print
  try {
    for (StrBlobPtr p = str_blob.begin(); ; p.incr()) {
      cout << p.deref() << endl;
    }
  }
  catch (out_of_range&) {
    // reach end => doing nothing
  }

  return 0;
}