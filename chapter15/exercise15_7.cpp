// Write <Quote> class (for different types of book-selling)
// With <Limited_quote> class: discount up to e.g. 10 copies; above that normal price
#include <iostream>

using namespace std;

class Quote {
public:
  Quote() = default;
  Quote(const string& book, double sales_price):
    bookNo(book), price(sales_price) {}

  string isbn() const { return bookNo; }
  virtual double net_price(size_t n) const {
    return n*price;
  }
  virtual ~Quote() = default; // NOTE: root of a tree ALWAYS defines virtual destructor

private:
  string bookNo; // ISBN number of this item

protected:
  double price = 0.0; // normal, undiscounted price
};

class Limited_quote: public Quote {
public:
  Limited_quote() = default;
  Limited_quote(const string& book, double p, size_t qty, double disc):
    Quote(book, p), max_qty(qty), discount(disc) {}
  double net_price(size_t n) const override;

private:
  // apply discount upto e.g. 10 books; above that apply normal price  
  size_t max_qty;
  double discount;
};

double Limited_quote::net_price(size_t cnt) const {
  if (cnt >= max_qty)
    return (1-discount)*price*max_qty + (cnt-max_qty)*price; // 1st 10 books discount; book 11, 12... normal price
  else 
    return cnt*(1-discount)*price;
}

double print_total(ostream& os, const Quote& item, size_t n) {
  double ret = item.net_price(n);
  os << "ISBN: " << item.isbn() << " #sold: " << n << " total due: " << ret << endl; 
  return ret;
}

int main() {
  Quote basic("CPP-111", 100);
  Limited_quote bulk("CPP-222", 100.0, 10, 0.2); // 20% discount for 1->10 copies; for 11th 12th book... normal price

  cout << "\n=== Regular quote ===\n";
  print_total(cout, basic, 5); // should be 5*100 = $500

  cout << "\n=== Limited Quote (still in discount range) ===\n";
  print_total(cout, bulk, 5); // should be 5*100*80% = $400

  cout << "\n=== Bulk Quote (above discount range) ===\n";
  print_total(cout, bulk, 15); // for 1st 10 books: 100*10*80%=$800; for the rest 5 books: 5*100=$500 => $1300 total 
  
  return 0;
}