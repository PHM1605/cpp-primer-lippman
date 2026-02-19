// Write <Sales_data> with overloaded operators
#include <iostream>

using namespace std;

class Sales_data {
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

Sales_data& Sales_data::operator+=(const Sales_data& rhs) {
  
}

// Non-member overloaded operators
ostream& operator<<(ostream& os, const Sales_data& item) {

}

istream& operator>>(istream& is, Sales_data& item) {

}

Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs) {

}



int main() {
  return 0;
}