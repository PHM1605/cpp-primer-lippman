// (Extend Exercise10_12) Write a conversion operator from <Sales_data> to <string> and <double>
// NOTE: they should NOT be explicit (only 'explicit' for <bool>)
#include <iostream>

using namespace std;

class Sales_data {
  friend ostream& operator<<(ostream&, Sales_data&);

public:
  Sales_data() = default;
  Sales_data(const string& s): bookNo(s) {}
  explicit Sales_data(const string&s, unsigned n, double p):
    bookNo(s), units_sold(n), revenue(p*n) {}

  string isbn() const { return bookNo; }

  // NEW: conversion operator
  operator string() const { return bookNo; }
  operator double() const { return revenue; }

private:
  string bookNo;
  unsigned int units_sold = 0;
  double revenue = 0.0;
};

ostream& operator<<(ostream& os, Sales_data& sd) {
  os << sd.isbn() << ": sold " << sd.units_sold << "; revenue: " << sd.revenue << endl;
  return os;
}



int main() {
  Sales_data book1(string("def456"), 3, 33);
  cout << book1 << endl;

  // Try to use conversion operator
  string isbn = book1;
  cout << "My ISBN is: " << isbn << endl;
  double rev = book1;
  cout << "My revenue is: " << rev << endl;

  return 0;
}