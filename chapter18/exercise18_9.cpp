// Extend the bookstore program with proper EXCEPTION handling
#include <iostream>
#include <fstream>

using namespace std;

class Sales_data {
public:
  Sales_data() = default;
  Sales_data(const string& s): bookNo(s) {}
  Sales_data(const string& s, unsigned n, double p):
    bookNo(s), units_sold(n), revenue(p*n) {}
  
  string isbn() const { return bookNo; }

  // Operators
  Sales_data& operator+=(const Sales_data&);
  friend istream& operator>>(istream&, Sales_data&);
  friend ostream& operator<<(ostream&, const Sales_data&);

private:
  string bookNo;
  unsigned int units_sold = 0;
  double revenue = 0.0;
};

// custom exception for Sales_data => use constructor of parents
class out_of_stock: public runtime_error {
public:
  explicit out_of_stock(const string& s):
    runtime_error(s) {}
};

class isbn_mismatch: public logic_error {
public:
  explicit isbn_mismatch(const string& s):
    logic_error(s) {}
  
  isbn_mismatch(const string& s, const string& lhs, const string& rhs):
    logic_error(s), left(lhs), right(rhs) {}

  const string left, right;
};

// Operators
Sales_data& Sales_data::operator+=(const Sales_data& rhs) {
  // NOTE: exception handling here
  if (isbn() != rhs.isbn()) {
    throw isbn_mismatch("wrong isbns", isbn(), rhs.isbn());
  }
  units_sold += rhs.units_sold;
  revenue += rhs.revenue;
  return *this;
}

Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs) {
  Sales_data sum = lhs;
  sum += rhs;
  return sum;
}

ostream& operator<<(ostream& os, const Sales_data& item) {
  os << "Isbn: " << item.isbn() << " "
    << "Units sold: " << item.units_sold << " "
    << "Revenue: " << item.revenue << endl;
  return os;
}

istream& operator>>(istream& is, Sales_data& item) {
  double price;
  is >> item.bookNo >> item.units_sold >> price;
  // if input successful
  if (is) {
    item.revenue = item.units_sold * price;
  } else {
    item = Sales_data();
  }
  return is;
}

int main() {
  Sales_data item1, item2, sum;
  ifstream infile("exercise18_9_input.txt");
  if (!infile) {
    cerr << "Cannot open file\n";
    return 1;
  }
  
  while (infile >> item1 >> item2) {
    try {
      sum = item1 + item2;
      cout << sum << endl;
    } catch (const isbn_mismatch& e) {
      cerr << e.what() << ": left isbn(" << e.left << ") right isbn(" << e.right << ")" << endl;
    }
  }

  return 0;
}