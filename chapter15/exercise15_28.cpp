// Write <vector> of <Quote> or <Bulk_quote> objects
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Quote {
public:
  Quote() = default;
  Quote(const string& book, double sales_price):
    bookNo(book), price(sales_price) {}
  virtual ~Quote() = default;

  string isbn() const { return bookNo; }
  virtual double net_price(size_t n) const { 
    cout << "Calling Quote::net_price()\n";
  return n*price; }

protected:
  double price = 0.0;

private:
  string bookNo;
};

class Bulk_quote: public Quote {
public:
  Bulk_quote() = default;
  Bulk_quote(const string& book, double p, size_t qty, double disc):
    Quote(book, p), min_qty(qty), discount(disc) {}
  
  double net_price(size_t n) const override;

private:
  size_t min_qty = 0;
  double discount = 0;
};

double Bulk_quote::net_price(size_t cnt) const {
  cout << "Calling Bulk_quote::net_price()\n";
  if (cnt >= min_qty)
    return cnt*(1-discount)*price;
  else 
    return cnt*price;
}

int main() {
  // vector can store either <Quote> or <Bulk_quote> pointerS
  vector<shared_ptr<Quote>> basket;
  basket.push_back(make_shared<Quote>("0-201-82470-1", 50));
  basket.push_back(make_shared<Bulk_quote>("0-201-54848-8", 50, 10, 0.25));
  cout << basket.back()->net_price(15) << endl;

  return 0;
}