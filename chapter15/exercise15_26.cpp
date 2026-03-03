// Bookstore program with copy-control members
#include <iostream>

using namespace std;

class Quote {
public:
  Quote() {
    cout << "[Quote] default constructor\n";
  }
  Quote(const string& book, double sales_price):
    bookNo(book), price(sales_price) {
      cout << "[Quote] book & price constructor\n";
    }
  Quote(const Quote& rhs):
    bookNo(rhs.bookNo), price(rhs.price) {
      cout << "[Quote] copy constructor\n";
    }
  Quote(Quote&& rhs):
    bookNo(std::move(rhs.bookNo)), price(std::move(rhs.price)) {
      cout << "[Quote] move constructor\n";
    }
  Quote& operator=(const Quote& rhs) {
    cout << "[Quote] copy assignment\n";
    if (this != &rhs) {
      bookNo = rhs.bookNo;
      price = rhs.price;
    }
    return *this;
  }
  Quote& operator=(Quote&& rhs) {
    cout << "[Quote] move assignment\n";
    if (this != &rhs) {
      bookNo = std::move(rhs.bookNo);
      price = std::move(rhs.price);
    }
    return *this;
  }
  virtual ~Quote() {
    cout << "[Quote] destructor\n";
  }

  // Aux functions
  string isbn() const { return bookNo; }
  virtual double net_price(size_t n) const {
    cout << "[Quote] net_price\n";
    return n*price;
  }
  virtual void debug() const {
    cout << "[Quote] debug\n";
    cout << " bookNo: " << bookNo << " price: " << price << endl;
  }
protected:
  double price = 0.0;

private:
  string bookNo;
};

class Bulk_quote: public Quote {
public:
  Bulk_quote() {
    cout << "[Bulk_quote] default constructor\n";
  }
  Bulk_quote(const string& book, double p, size_t qty, double disc):
    Quote(book, p), min_qty(qty), discount(disc) {
      cout << "[Bulk_quote] (book, p, qty, disc) constructor\n";
  }
  Bulk_quote(const Bulk_quote& rhs):
    Quote(rhs), min_qty(rhs.min_qty), discount(rhs.discount) {
      cout << "[Bulk_quote] copy constructor\n";
    }
  Bulk_quote& operator=(const Bulk_quote& rhs) {
    cout << "[Bulk_quote] copy assignment\n";
    if (this != &rhs) {
      Quote::operator=(rhs); // assign base part
      min_qty = rhs.min_qty;
      discount = rhs.discount;
    }
    return *this;
  }
  ~Bulk_quote() override {
    cout << "[Bulk_quote] destructor\n";
  }

  double net_price(size_t cnt) const override {
    cout << "[Bulk_quote] net_price\n";
    if (cnt >= min_qty)
      return cnt*(1-discount)*price;
    else
      return cnt*price;
  }

  void debug() const override {
    cout << "[Bulk_quote] debug\n";
    cout << " bookNo: " << isbn() << " price: " << price << " min_qty: " << min_qty << " discount: " << discount << endl;
  }

private:
  size_t min_qty = 0;
  double discount = 0;
}; 

// to check if <Quote> or <Bulk_quote> is ran into this function 
double print_total(const Quote& item, size_t n) {
  cout << "---- print_total ----\n";
  double ret = item.net_price(n);
  cout << "Total due: " << ret << endl;
  return ret;
}

int main() {
  cout << "\n=== Construct objects ===\n";
  Quote basic("CPP-111", 50.0);
  Bulk_quote bulk("CPP-222", 50.0, 10, 0.2);

  cout << "\n=== Debug calls ===\n";
  basic.debug();
  bulk.debug();

  cout << "\n=== Dynamic Binding test ===\n";
  print_total(basic, 5); // will call Quote::net_price
  print_total(bulk, 15); // will call Bulk_quote::net_price

  cout << "\n=== Copy construction ===\n";
  Bulk_quote bulk2 = bulk;

  cout << "\n=== Copy assignment ===\n";
  Bulk_quote bulk3;
  bulk3 = bulk;

  cout << "\n=== Trimming <Bulk_quote> to barebone <Quote> ===\n";
  Quote trimmed = bulk;
  print_total(trimmed, 15);

  cout << "\n=== End of main ===\n";
  return 0;
}