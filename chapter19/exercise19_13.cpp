// Modify <Sales_data>: define a type that can represent a pointer to <bookNo>
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

  // NEW: static function to get "pointer-to-member"
  static const string Sales_data::* get_pISBN() {
    return &Sales_data::bookNo;
  }

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

  // define a "pointer-to-member" to "bookNo"
  const string Sales_data::* pBookNo = Sales_data::get_pISBN();
  cout << "ISBN via pointer-to-member: " << sd.*pBookNo << endl;

  return 0;
}