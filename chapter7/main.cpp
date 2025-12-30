// print the sales of all books with different ISBNs
// assuming sales are sorted in ISBN order
#include <iostream>
#include "Sales_data.h"

int main() {
  Sales_data total; // to hold the running sum

  if (read(cin, total)) { // read the first transaction into <total>
    Sales_data trans; // next transaction holder
    while(read(cin, trans)) {
      // if this transaction has same ISBN => sum it up
      if (total.isbn() == trans.isbn())
        total.combine(trans);
      // different ISBN => print the total sales of that ISBN book and move on to next ISBN book
      else {
        print(cout, total) << endl;
        total = trans;
      } 
    }
    // print the last ISBN sum
    print(cout, total) << endl;

  } else {
    cerr << "No data?!" << endl;
  }

  return 0;
}