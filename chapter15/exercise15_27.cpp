// Write <Bulk_quote> that inherits its constructors
#include <iostream>

using namespace std;

class Quote {
public:
  Quote() = default;
  Quote(const string& book, double sales_price):
    bookNo(book), price(sales_price) {}
  virtual ~Quote() = default;

  string isbn() const { return bookNo; }
  virtual double net_price(size_t n) const {
    return n*price;
  }
  virtual void debug(){
    cout << "bookNo: " << bookNo << "; price: " << price << endl;
  }

protected:
  double price = 0.0;

private:
  string bookNo;
};

// Abstract class 
class Disc_quote: public Quote {
public:
  Disc_quote() = default;
  Disc_quote(const string& book, double price, size_t qty, double disc):
    Quote(book, price), quantity(qty), discount(disc) {}
  // NOTE: abstract
  double net_price(size_t) const = 0;

private:
  size_t quantity = 0;
  double discount = 0;
};

class Bulk_quote: public Disc_quote {
public:
  // NEW: inherit constructors
  using Disc_quote::Disc_quote;
  // override abstract function
  double net_price(size_t n) const override;

  void debug() override {
    cout << "bookNo: " << isbn() << "; price: " << price << "; min_qty" << min_qty << "; discount: " << discount << endl; 
  }
private:
  size_t min_qty = 0;
  double discount = 0;
};

double Bulk_quote::net_price(size_t n) const {
  if (n>=min_qty)
    return n*price*(1-discount);
  else 
    return n*price;
}

// print depends on which version, <Quote> or <Bulk_quote>
double print_total(ostream& os, const Quote& item, size_t n) {
  double ret = item.net_price(n);
  os << "ISBN: " << item.isbn() << " #sold: " << n << " total due: " << ret << endl;
  return ret;
}

int main() {
  Quote basic("CPP-111", 50.0);
  Bulk_quote bulk("CPP-222", 50.0, 10, 0.1);

  cout << "\n=== Regular quote ===\n";
  print_total(cout, basic, 5);
  cout << "\n=== Bulk quote ===\n";
  print_total(cout, bulk, 15);

  cout << "\n=== Debug ===\n";
  basic.debug();
  bulk.debug();

  return 0;
}