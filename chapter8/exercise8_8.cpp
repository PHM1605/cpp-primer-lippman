// Revise the Bookstore program, to APPEND its output to a given file
// Run this command TWICE to check:
// ./a.out sales_data_input.txt output_8_8.txt
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Sales_data {
// friends
friend istream& read(istream&, Sales_data&); 
friend ostream& print(ostream&, const Sales_data&);

public:
  // constructors
  Sales_data() = default;

  // operations
  string isbn() const { return bookNo; }
  Sales_data& combine(const Sales_data&); 
  
private:
  string bookNo;
  unsigned units_sold = 0;
  double revenue = 0.0;
  // private operations
  inline double avg_price() const { return units_sold ? revenue/units_sold : 0; }
};

// non member functions to interact with Sales_data
istream& read(istream&, Sales_data&); // read <istream> to <Sales_data>
ostream& print(ostream&, const Sales_data&);

// implementation
Sales_data& Sales_data::combine(const Sales_data& rhs) {
  units_sold += rhs.units_sold;
  revenue += rhs.revenue;
  return *this;
}

istream& read(istream& is, Sales_data& item) {
  double price = 0;
  is >> item.bookNo >> item.units_sold >> price;
  item.revenue = price * item.units_sold;
  return is;
}

ostream& print(ostream& os, const Sales_data& item) {
  os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
  return os;
}

int main(int argc, char* argv[]) {
  ifstream input(argv[1]); // open the data file of transactions
  ofstream output(argv[2], ofstream::app); // open the output file in APPEND mode

  Sales_data total;

  // read the 1st transaction
  if (read(input, total)) {
    Sales_data trans; // holding next transaction
    // read the remaining transactions
    while(read(input, trans)) {
      if (total.isbn() == trans.isbn()) // add up if same <isbn>
        total.combine(trans);
      else {
        print(output, total) << endl; // print the result
        total = trans;
      }
    }
    print(output, total) << endl;
  } else {
    cerr << "No data?!" << endl;
  }

  return 0;
}