// Write <Quote> class (different types of book-selling)
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

class Bulk_quote: public Quote {
public:
  Bulk_quote() = default;
  Bulk_quote(const string& book, double p, size_t qty, double disc):
    Quote(book, p), min_qty(qty), discount(disc) {}
  double net_price(size_t n) const override;

private:
  // minimum purchase for the discount to apply (0 < discount <=1)
  size_t min_qty = 0;
  double discount = 0;
};

double Bulk_quote::net_price(size_t cnt) const {
  if (cnt >= min_qty)
    return cnt*(1-discount)*price;
  else 
    return cnt*price;
}

double print_total(ostream& os, const Quote& item, size_t n) {
  double ret = item.net_price(n);
  os << "ISBN: " << item.isbn() << " #sold: " << n << " total due: " << ret << endl; 
  return ret;
}

int main() {
  Quote basic("CPP-111", 50.0);
  Bulk_quote bulk("CPP-222", 50.0, 10, 0.2); // 20% discount if >= 10 copies

  cout << "\n=== Regular quote ===\n";
  print_total(cout, basic, 5);

  cout << "\n=== Bulk Quote (below discount) ===\n";
  print_total(cout, bulk, 5); // no discount 

  cout << "\n=== Bulk Quote (with discount) ===\n";
  print_total(cout, bulk, 15); // discount applied
  
  return 0;
}