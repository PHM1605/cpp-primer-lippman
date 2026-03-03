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
protected:
  double price = 0.0;

private:
  string bookNo;
};



int main() {
  return 0;
}