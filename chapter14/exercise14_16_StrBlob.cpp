// Extend <StrBlob> to have operator== and operator!=
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class StrBlob {
  friend bool operator==(const StrBlob&, const StrBlob&);
  friend bool operator!=(const StrBlob&, const StrBlob&);
  friend bool operator<(const StrBlob&, const StrBlob&);
  friend bool operator>(const StrBlob&, const StrBlob&);
public:
  StrBlob();
  StrBlob(initializer_list<string> il);

  string& operator[](size_t);

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

bool operator<(const StrBlob& a, const StrBlob& b) {
  return *a.data < *b.data;
}

bool operator>(const StrBlob& a, const StrBlob& b) {
  return *a.data > *b.data;
}

string& StrBlob::operator[](size_t n) {
  return (*data)[n];
}

int main() {
  cout << "=== Test operator== and operator!= ===\n";
  StrBlob a({"one", "two", "three"});
  StrBlob b({"one", "three"});
  StrBlob c({"one", "three"});

  cout << "Does a equals b? " << (a==b) << endl;
  cout << "Is a different to b? " << (a!=b) << endl;
  cout << "Does b equals c? " << (b==c) << endl;
  cout << "Is b different to c? " << (b!=c) << endl;

  cout << "=== Test operator< and operator> ===\n";
  cout << "a>b ? " << (a>b) << endl;
  cout << "b>a ? " << (b>a) << endl;

  cout << "\n=== Test operator[] ===\n";
  cout << "a[0] before: " << a[0] << endl;
  a[0] = "ONE";
  cout << "a[0] after: " << a[0] << endl;
  
  return 0;
}