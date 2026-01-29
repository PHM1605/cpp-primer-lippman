// Extended <StrBlob> class (share string data among objects) with:
// 1/ copy constructor
// 2/ copy-assignment
// NOTE: destructor NO NEED (as <shared_ptr> handles data)
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class StrBlob {
public:
  StrBlob();
  StrBlob(initializer_list<string> il);
  // copy constructor
  StrBlob(const StrBlob&);
  // copy assignment
  StrBlob& operator=(const StrBlob&);

  size_t size() const { return data->size(); }
  bool empty() const { return data->empty(); }
  void push_back(const string& t) { data->push_back(t); }
  void pop_back();

  string& front();
  string& back();
  const string& front() const;
  const string& back() const;

private:
  shared_ptr<vector<string>> data;
  // throw <msg> if data[i] isn't valid
  void check(size_t i, const string& msg) const;
};

StrBlob::StrBlob():
  data(make_shared<vector<string>>()) {}

StrBlob::StrBlob(initializer_list<string> il):
  data(make_shared<vector<string>>(il)) {}

StrBlob::StrBlob(const StrBlob& rhs):
  data(make_shared<vector<string>>(*rhs.data)) {}

StrBlob& StrBlob::operator=(const StrBlob& rhs) {
  data = make_shared<vector<string>>(*rhs.data);
  return *this;
}

void StrBlob::pop_back() {
  check(0, "pop_back on empty StrBlob");
  data->pop_back();
}

string& StrBlob::front() {
  check(0, "front on empty StrBlob");
  return data->front();
}

string& StrBlob::back() {
  check(0, "back on empty StrBlob");
  return data->back();
}

const string& StrBlob::front() const {
  check(0, "front on empty StrBlob");
  return data->front();
}

const string& StrBlob::back() const {
  check(0, "back on empty StrBlob");
  return data->back();
}

void StrBlob::check(size_t i, const string& msg) const {
  if (i>=data->size()) 
    throw out_of_range(msg);
}



int main() {
  StrBlob b1({"hello", "world"});
  StrBlob b2 = b1; // test copy constructor
  StrBlob b3;
  b3 = b1; // test copy assignment

  cout << "Before modification:\n";
  cout << "b1 front = " << b1.front() << endl;
  cout << "b2 front = " << b2.front() << endl;
  cout << "b3 front = " << b3.front() << endl;

  // modify b1
  b1.front() = "HELLO";

  // we prove that after modify <b1>, other 2 aren't affected
  cout << "\nAfter modifying b1:\n";
  cout << "b1 front = " << b1.front() << endl;
  cout << "b2 front = " << b2.front() << endl;
  cout << "b3 front = " << b3.front() << endl;

  return 0;
}