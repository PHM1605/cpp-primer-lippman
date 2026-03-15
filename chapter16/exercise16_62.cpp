// Define <Sales_data> with specialization hash<Sales_data> (generate hash code)
#include <iostream>
#include <vector>
#include <unordered_set>
#include <functional> // for XOR ^ operator

using namespace std;

class Sales_data {
  friend bool operator==(const Sales_data&, const Sales_data&);
  // NEW: to let <hash> access <Sales_data>'s members
  friend class std::hash<Sales_data>;

public:
  Sales_data() = default;
  Sales_data(const string& s): bookNo(s) {}
  Sales_data(const string& s, unsigned n, double p):
    bookNo(s), units_sold(n), revenue(p*n) {}

  string isbn() const { return bookNo; }

private:
  string bookNo;
  unsigned int units_sold = 0;
  double revenue = 0.0;
};

bool operator==(const Sales_data& lhs, const Sales_data& rhs) {
  return lhs.isbn()==rhs.isbn() && lhs.units_sold==rhs.units_sold && lhs.revenue==rhs.revenue;
}
bool operator!=(const Sales_data& lhs, const Sales_data& rhs) {
  return !(lhs==rhs);
}

// Specialization <hash> (generate hash code)
namespace std {
template<>
struct hash<Sales_data> {
  typedef size_t result_type;
  typedef Sales_data argument_type; // NOTE: this (e.g. Sales_data) will need "==" definition
  size_t operator() (const Sales_data&) const;
};

size_t hash<Sales_data>::operator()(const Sales_data& s) const {
  return hash<string>()(s.bookNo) ^ // ^: operator XOR
    hash<unsigned>()(s.units_sold) ^
    hash<double>()(s.revenue);
}
}

int main() {
  Sales_data s1("book1", 10, 5.0);
  hash<Sales_data> h;
  cout << "hash value: " << h(s1) << endl;

  // will automatically use hash<Sales_data>
  unordered_multiset<Sales_data> SDSet;
  SDSet.insert(s1);
  cout << "container size: " << SDSet.size() << endl;

  return 0;
}