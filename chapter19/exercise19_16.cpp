// Modify <Sales_data>: define a type that can represent an alias to "pointer-to-member-function" <avg_price>
#include <iostream>

using namespace std;

class Sales_data{
  friend ostream& operator<<(ostream&, const Sales_data&);

public:
  // constructors 
  Sales_data() = default;
  Sales_data(const string &s): bookNo(s) {}
  Sales_data(const string& s, unsigned n, double price):
    bookNo(s), units_sold(n), revenue(price*n) {}

  // NEW: define alias to type "pointer-to-member-function"
  double avg_price() { 
    return units_sold ? revenue/units_sold : 0;
  }
  using AvgPricePtr = double (Sales_data::*)();

private:
  string bookNo;
  unsigned units_sold = 0;
  double revenue = 0;
};  

ostream& operator<<(ostream& os, const Sales_data& sd) {
  cout << "ISBN: " << sd.bookNo << "; units sold: " << sd.units_sold << "; revenue: " << sd.revenue << endl;
  return os;
}

int main() {
  Sales_data sd = Sales_data("Cpp Primer", 2, 50);
  cout << sd << endl;
  // get pointer to member function AND ATTACH to above object
  Sales_data::AvgPricePtr ptr = &Sales_data::avg_price;
  cout << "Average price is: " << (sd.*ptr)() << endl;

  return 0;
}