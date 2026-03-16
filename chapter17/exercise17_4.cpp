// Rewrite an advance bookstoreS program with <findBook> function
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <tuple>

using namespace std;

class Sales_data {
public:
  Sales_data() = default;
  Sales_data(const string& s): bookNo(s) {}
  Sales_data(const string& s, unsigned n, double p):
    bookNo(s), units_sold(n), revenue(n*p) {}

  string isbn() const { return bookNo; }
  Sales_data& operator+=(const Sales_data&);
  

private:
  string bookNo;
  unsigned int units_sold = 0;
  double revenue = 0.0;
};

bool compareIsbn(const Sales_data& sd1, const Sales_data& sd2) {
  return sd1.isbn() < sd2.isbn();
}

Sales_data& Sales_data::operator+=(const Sales_data& rhs) {
  units_sold += rhs.units_sold;
  revenue += rhs.revenue;
  return *this;
}

ostream& operator<<(ostream& os, const Sales_data& s) {
  os << s.isbn();
  return os;
}

Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs) {
  Sales_data sum = lhs;
  sum += rhs;
  return sum;
}

// matches: tuple of "store index", 2 "iterators" of matched ISBN
typedef tuple<
  size_t,
  vector<Sales_data>::const_iterator,
  vector<Sales_data>::const_iterator
> matches; 

// files: all stores' transactions
vector<matches> findBook(const vector<vector<Sales_data>> &files, const string& book) {
  vector<matches> ret;
  // for each store find range of matching books, if any
  for (auto it=files.cbegin(); it!=files.cend(); ++it) {
    // find the range of Sales_data that have the same ISBN
    auto found = equal_range(it->cbegin(), it->cend(), Sales_data(book,0,0), compareIsbn);
    if (found.first != found.second) {
      ret.push_back(make_tuple(it-files.cbegin(), found.first, found.second));
    }
  }
  return ret;
}

void reportResults(istream& in, ostream& os, const vector<vector<Sales_data>>& files) {
  string s; // book to look for
  while(in >> s) {
    auto trans = findBook(files, s); // stores that sold this book
    if (trans.empty()) {
      os << s << " not found in any stores" << endl;
      continue;
    }
    // for every store with a sale
    for (const auto& store: trans) {
      os << "store " << get<0>(store) << " sales: " 
        << accumulate(get<1>(store), get<2>(store), Sales_data(s)) << endl;
    }
  }
}

int main() {
  vector<vector<Sales_data>> stores = {
    {{"book1",5,10}, {"book1",3,10}, {"book2",4,20}},
    {{"book1",2,10}, {"book3",6,15}},
    {{"book2",3,20}, {"book3",5,15}}
  };

  // for each store, sort based on ISBN
  for(auto& store: stores) {
    sort(store.begin(), store.end(), compareIsbn);
  }
  ifstream input("exercise17_4_input.txt");
  reportResults(input, cout, stores);

  return 0;
}