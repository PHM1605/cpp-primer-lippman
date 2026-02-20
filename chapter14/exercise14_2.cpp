// Write <Sales_data> with overloaded operators
#include <iostream>
#include <sstream>

using namespace std;

class Sales_data {
  friend ostream& operator<<(ostream&, const Sales_data&);
  friend istream& operator>>(istream&, Sales_data&);
  friend bool operator==(const Sales_data&, const Sales_data&);
public:
  // constructor
  Sales_data() = default;
  Sales_data(const string& s): bookNo(s) {}
  Sales_data(const string& s, unsigned n, double p):
    bookNo(s), units_sold(n), revenue(p*n) {}
  
  string isbn() const { return bookNo; }
  double avg_price() const;

  // Overloaded operators
  Sales_data& operator+=(const Sales_data&);

private:
  string bookNo;
  unsigned int units_sold = 0;
  double revenue = 0.0;
};

double Sales_data::avg_price() const {
  if (units_sold)
    return revenue/units_sold;
  else 
    return 0;
}

// left-operand refers to <this>
// assume both refer to SAME book
Sales_data& Sales_data::operator+=(const Sales_data& rhs) {
  units_sold += rhs.units_sold;
  revenue += rhs.revenue;
  return *this;
}

// Non-member overloaded operators
ostream& operator<<(ostream& os, const Sales_data& item) {
  os << "Isbn: " << item.isbn() << " " 
    << "Units sold: " << item.units_sold << " " 
    << "Revenue: " << item.revenue << " " 
    << "Avg price: " << item.avg_price();
  return os;
}

istream& operator>>(istream& is, Sales_data& item) {
  double price;
  is >> item.bookNo >> item.units_sold >> price;
  if (is) // check if input succeeded
  {
    item.revenue = item.units_sold * price;
    // is.setstate(ios::eofbit); // optional
  }    
  else {
    item = Sales_data(); // input failed: give object default value
  }
    
  return is;
}

// assuming both objects refer to the same book
Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs) {
  Sales_data sum = lhs;
  sum += rhs;
  return sum;
}

bool operator==(const Sales_data& lhs, const Sales_data& rhs) {
  return lhs.isbn() == rhs.isbn() && lhs.units_sold == rhs.units_sold && lhs.revenue==rhs.revenue;
}
bool operator!=(const Sales_data& lhs, const Sales_data& rhs) {
  return !(lhs==rhs);
}

int main() {
  cout << "=== Test valid input ===\n";
  stringstream good("0-201-99999-9 10 24.95");
  stringstream bad("10 24.95 0-210-99999-9");
  
  Sales_data s1;
  if (good >> s1)
    cout << "Valid: " << s1 << endl;
  else
    cout << "Invalid input\n";

  Sales_data s2;
  if (bad >> s2) 
    cout << s2 << " Valid (should not happen)\n";
  else 
    cout << "Correctly rejected\n";

  cout << "\n=== Test operator+ ===\n";
  stringstream ss1("0-201-99999-9 5 20.0");
  stringstream ss2("0-201-99999-9 3 20.0");
  Sales_data sd1, sd2;
  ss1 >> sd1;
  ss2 >> sd2;
  Sales_data sum_sd1_sd2 = sd1 + sd2;
  cout << "First: " << sd1 << endl;
  cout << "Second: " << sd2 << endl;
  cout << "Sum: " << sum_sd1_sd2 << endl;

  cout << "\n=== Test operator== ===\n";
  stringstream ss3("0-201-99999-9 5 20.0");
  Sales_data sd3;
  ss3 >> sd3;
  cout << "1 and 3 same? " << (sd3 == sd1) << endl;
  cout << "1 and 2 different? " << (sd2 != sd1) << endl;

  return 0;
}