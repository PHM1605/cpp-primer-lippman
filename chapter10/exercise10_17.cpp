// Sort a vector<Sales_data> WITH LAMBDA
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


class Sales_data {
// friend
friend ostream& print(ostream&, Sales_data&);

public:
  // constructor
  Sales_data() = default;
  Sales_data(const string& s): bookNo(s) {}
  explicit Sales_data(const string& s, unsigned n, double p):
    bookNo(s), units_sold(n), revenue(p*n) {}

  // operations
  string isbn() const {return bookNo;}

private:
  string bookNo;
  unsigned int units_sold = 0;
  double revenue = 0.0;
};

ostream& print(ostream& os, Sales_data& sd) {
  os << sd.isbn() << ": sold " << sd.units_sold << "; revenue: " << sd.revenue << endl;
  return os;
}

int main() {
  Sales_data book_1(string("def456"), 3, 33); // 33$ book, 3 sold
  Sales_data book_2(string("abc123"), 2, 25); // 25$ book, 2 sold
  vector<Sales_data> vsd {book_1, book_2};

  cout << "Sales data before sort:\n"; 
  for (auto& item: vsd) 
    print(cout, item);

  sort(
    vsd.begin(), vsd.end(),
    [](Sales_data& sd1, Sales_data& sd2) {
      return sd1.isbn() < sd2.isbn();
    }
  );

  cout << "Sales data after sort:\n";
  for (auto& item: vsd)
    print(cout, item);

  return 0;
}