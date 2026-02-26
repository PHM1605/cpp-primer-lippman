// Write <Quote> class (different types of book-selling)
#include <iostream>

using namespace std;

class Quote {
public:
  Quote() = default;

  string isbn() const;
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
  double net_price(size_t n) const override;
};

double print_total(ostream& os, const Quote& item, size_t n) {
  double ret = item.net_price(n);
  os << "ISBN: " << item.isbn() << " #sold: " << n << " total due: " << ret << endl; 
  return ret;
}

int main() {
  return 0;
}