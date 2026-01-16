// Define an ITERATOR that takes from <multiset>.begin()
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

bool compareIsbn(const Sales_data& lhs, const Sales_data& rhs) {
  return lhs.isbn() < rhs.isbn();
}

int main() {
  multiset<Sales_data, bool(*)(const Sales_data&, const Sales_data&)> bookstore(&compareIsbn);
  // put some data in
  bookstore.insert(Sales_data("978-2", 10, 20.0));
  bookstore.insert(Sales_data("978-1", 5, 30.0));
  bookstore.insert(Sales_data("978-3", 2, 50.0));

  // get iterator out
  multiset<Sales_data, bool(*)(const Sales_data&, const Sales_data&)>::iterator it = bookstore.begin();
  cout << "First ISBN in bookstore: " << it->isbn() << endl;
  cout << "All ISBNs in order:\n";
  for (; it!=bookstore.end(); ++it) {
    cout << it->isbn() << endl;
  }
  
  return 0;
}