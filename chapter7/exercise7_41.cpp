#include <iostream>
#include <string>

using namespace std;

// Rewrite Sales_data using delegate constructor
class Sales_data {

friend istream& read(istream&, Sales_data&);

public:
  Sales_data(string s, unsigned int cnt, double price):
    bookNo(s), units_sold(cnt), revenue(cnt*price) {}
  // delegates to above
  Sales_data(): Sales_data("", 0, 0) {}
  Sales_data(string s): Sales_data(s, 0, 0) {}
  Sales_data(istream& is): Sales_data() {
    read(is, *this);
  }
private:
  string bookNo;
  unsigned units_sold = 0;
  double revenue = 0.0;
};

istream& read(istream&, Sales_data&);