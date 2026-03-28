// From a vector<Sales_data> write a function to find the 1st element whose "average_price" higher than a "double"
#include <iostream>
#include <vector>
#include <algorithm> // for find_if
#include <functional> // for "function"

using namespace std;

class Sales_data{
  friend ostream& operator<<(ostream&, const Sales_data&);

public:
  // constructors 
  Sales_data() = default;
  Sales_data(const string &s): bookNo(s) {}
  Sales_data(const string& s, unsigned n, double price):
    bookNo(s), units_sold(n), revenue(price*n) {}

  double avg_price() { 
    return units_sold ? revenue/units_sold : 0;
  }

  // NEW: create member-function for using POINTER later
  bool priceAbove(double threshold) {
    return avg_price() > threshold;
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

vector<Sales_data>::iterator firstMatch(vector<Sales_data>& vec, double threshold) {
  function<bool (Sales_data&)> fcn = bind(&Sales_data::priceAbove, placeholders::_1, threshold);
  return find_if(vec.begin(), vec.end(), fcn);
}

int main() {
  vector<Sales_data> vec = {
    Sales_data("Cpp Primer", 10, 10),
    Sales_data("B++", 5, 50), // only this has price > threshold (30)
    Sales_data("C++", 2, 20)
  };
  double threshold= 30;
  auto it = firstMatch(vec, threshold);
  if (it != vec.end()) {
    cout << "First match: " << *it << endl;
  } else {
    cout << "No match found\n";
  }

  return 0;
}