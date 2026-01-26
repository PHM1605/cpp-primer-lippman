// Extended <StrBlob> class (share string data among objects) with destructor, etc.
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class StrBlob {
public:
  StrBlob();
  StrBlob(initializer_list<string> il);

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

  return 0;
}