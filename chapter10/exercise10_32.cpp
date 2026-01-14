// Rewrite the Bookstore program
// - use <vector> to hold transactions; 
// - use <sort> & <compareIsbn> to sort; 
// - use <find> & <accumulate> to do the sum
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <fstream>
#include <numeric> // for <accumulate>

using namespace std;

class Sales_data {
friend istream& operator>>(istream&, Sales_data&);
friend ostream& operator<<(ostream&, Sales_data&);

public:
  Sales_data() = default;
  Sales_data(const string& s, unsigned n, double p):
    bookNo(s), units_sold(n), revenue(n*p) {}

  string isbn() { return bookNo; }
  Sales_data& operator+=(const Sales_data&);

private:
  string bookNo;
  unsigned int units_sold=0;
  double revenue = 0.0;
};

Sales_data& Sales_data::operator+=(const Sales_data& rhs) {
  units_sold += rhs.units_sold;
  revenue += rhs.revenue;
  return *this;
}

bool compareIsbn(Sales_data& sd1, Sales_data& sd2) {
  return sd1.isbn() < sd2.isbn();
}

istream& operator>>(istream& is, Sales_data& sd) {
  double price;
  is >> sd.bookNo >> sd.units_sold >> price;
  // if inputs succeeded
  if (is)
    sd.revenue = sd.units_sold * price;
  // input failed: reset ofject to default
  else 
    sd = Sales_data();
  return is;
}

ostream& operator<<(ostream& os, Sales_data& sd) {
  os << sd.isbn() << ": sold " << sd.units_sold << "; revenue " << sd.revenue << endl;
  return os;
}

int main(){
  fstream fs ("exercise10_32_input.txt");
  istream_iterator<Sales_data> is_sd(fs), eof;
  // use istream_iterator to auto read <vector>
  vector<Sales_data> vsd(is_sd, eof);
  // sort based on ISBN
  sort(
    vsd.begin(), vsd.end(),
    compareIsbn
  );
  // debug print
  cout << "Original sorted vector:\n";
  for (auto& item: vsd) {
    cout << item;
  }

  // <find> and <accumulate>
  cout << "Accumulated:\n";
  auto iter = vsd.begin();
  while(iter != vsd.end()) {
    // find 1st element which has different ISBN with current
    auto next_grp = find_if(
      iter, vsd.end(),
      [iter](Sales_data& sd) {
        return sd.isbn() != iter->isbn();
      }
    );
    Sales_data sum_sales = accumulate(
      iter+1, next_grp, 
      *iter, // init value of Sales_data
      [](Sales_data total, const Sales_data& curr) {
        total += curr;
        return total;
      }
    );
    cout << sum_sales;
    iter = next_grp;
  }



  return 0;
}