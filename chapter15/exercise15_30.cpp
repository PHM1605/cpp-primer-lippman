// Write <Basket> class and compute prices for transactions
#include <iostream>
#include <memory>
#include <set>

using namespace std;

class Quote {
public:
  Quote() = default;
  Quote(const string& book, double sales_price):
    bookNo(book), price(sales_price) {}
  virtual ~Quote() = default;

  string isbn() const { return bookNo; }
  virtual double net_price(size_t cnt) const {
    return cnt*price;
  }
  // & at the end means MUST BE CALLED ON <LVALUE>
  virtual Quote* clone() const & {
    cout << "Clone <Quote> with <copy>\n";
    return new Quote(*this);
  }
  // & at the end means CAN BE CALLED ON <RVALUE>
  virtual Quote* clone() && {
    cout << "Clone <Quote> with <move>\n";
    return new Quote(std::move(*this));
  }

private:
  string bookNo;
protected:
  double price = 0.0;
};

class Bulk_quote: public Quote {
public:
  Bulk_quote() = default;
  Bulk_quote(const string& book, double p, size_t qty, double disc):
    Quote(book, p), min_qty(qty), discount(disc) {}
  
  double net_price(size_t cnt) const override {
    if (cnt >= min_qty)
      return cnt*(1-discount) * price;
    else
      return cnt*price;
  }
  // cloning must be called on <lvalue>
  Bulk_quote* clone() const & {
    cout << "Clone <Bulk_quote> with <copy>\n";
    return new Bulk_quote(*this);
  }
  // cloning can be called on <rvalue> 
  Bulk_quote* clone() && {
    cout << "Clone <Bulk_quote> with <move>\n";
    return new Bulk_quote(move(*this));
  }

private:
  size_t min_qty = 0;
  double discount = 0;
};

class Basket {
public:
  void add_item(const shared_ptr<Quote>& sale) {
    cout << "add_item() with pointer\n";
    items.insert(sale);
  }
  double total_receipt(ostream&) const;

  // add item with object (instead of pointers)
  // <lvalue> version of clone()
  void add_item(const Quote& sale) {
    cout << "add_item() with object\n";
    items.insert(shared_ptr<Quote>(sale.clone()));
  }
  // <rvalue> version of clone()
  void add_item(Quote&& sale) {
    cout << "add_item() with object\n";
    items.insert(shared_ptr<Quote>(std::move(sale).clone()));
  }

private:
  static bool compare(const shared_ptr<Quote>& lhs, const shared_ptr<Quote>& rhs) {
    return lhs->isbn() < rhs->isbn();
  }
  // store "pointers-to-transactions"; being sorted by "pointer to compare function"
  // NOTE: set of items HAS BEEN SORTED in ascending order
  multiset<shared_ptr<Quote>, decltype(compare)*> items {compare};
};

double print_total(ostream& os, const Quote& item, size_t n) {
  double ret = item.net_price(n);
  os << "ISBN: " << item.isbn() << " #sold: " << n << " total due: " << ret << endl;
  return ret;
}

double Basket::total_receipt(ostream& os) const {
  double sum = 0.0; // holds the running total
  // upper_bound: moves to the next keyword in <multiset>
  for (auto iter=items.cbegin(); iter != items.cend(); iter=items.upper_bound(*iter)) {
    sum += print_total(os, **iter, items.count(*iter));
  }
  os << "Total Sale: " << sum << endl; 
  return sum;
}

int main() {
  Basket bsk;
  bsk.add_item(make_shared<Quote>("123", 45));
  bsk.add_item(make_shared<Bulk_quote>("345", 45, 3, 0.15));

  cout << "\nStart add_item() with object allocation\n";
  bsk.add_item(Quote("123", 45));
  bsk.add_item(Bulk_quote("101112", 69, 5, 0.2));

  cout << "\nTotal receipt\n";
  bsk.total_receipt(cout);

  return 0;
}