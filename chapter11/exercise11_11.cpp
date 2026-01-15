// Rewrite the <bookstore> program that uses <multiset>
// <key>s are ISBN numbers, arranged based on CUSTOM ISBN COMPARE
// => sort in ISBN order
#include <iostream>
#include <set>

using namespace std;

class Sales_data {
public:
  Sales_data() = default;
  Sales_data(const string& s, unsigned n, double price):
    bookNo(s), units_sold(n), revenue(n*price) {}

public:
  string isbn() const { return bookNo; }

private:
  string bookNo;
  unsigned int units_sold = 0;
  double revenue = 0.0;
};

// custom compare function to be passed to <multiset>
bool compareIsbn(const Sales_data& lhs, const Sales_data& rhs) {
  return lhs.isbn() < rhs.isbn();
}

int main() {
  // // NOTE: short simple way; we must create multiset with that custom operation
  // multiset<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn);

  // long explicit way
  multiset<Sales_data, bool (*)(const Sales_data&, const Sales_data&)> bookstore(&compareIsbn);

  // test data 
  bookstore.insert(Sales_data("978-3", 5, 10.0));
  bookstore.insert(Sales_data("978-1", 2, 12.0));
  bookstore.insert(Sales_data("978-2", 3, 15.0));
  bookstore.insert(Sales_data("978-1", 4, 12.0)); // duplicated entry

  // print 
  for (const auto& item: bookstore) {
    cout << item.isbn() << endl;
  }

  return 0;
}