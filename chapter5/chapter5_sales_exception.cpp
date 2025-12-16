// Usage: 
// g++  chapter5_sales_exception.cpp
// ./a < chapter5_sales_data_input.txt
#include <iostream>
#include <stdexcept>
#include "Sales_item.h"

using namespace std;

int main() {
  Sales_item item1, item2;
  while (cin >> item1 >> item2) {
    try {
      if (item1.isbn() != item2.isbn()) 
        throw runtime_error("Data must refer to the same ISBN");
      cout << item1 + item2 << endl;
    } catch(runtime_error err) {
      cout << err.what() 
        << "\nTry Again? Enter y or n" << endl;
      char c;
      cin >> c;
      if (!cin || c=='n')
        break;
    }
  }
  return 0;
}