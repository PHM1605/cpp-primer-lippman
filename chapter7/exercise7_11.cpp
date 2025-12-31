// Write a program to use <Sales_data> constructors
// g++ exercise7_11.cpp Sales_data.cpp
#include <iostream>
#include "Sales_data.h"

using namespace std;

int main() {
  Sales_data sales_data_1 = Sales_data("The Art of Electronics");
  print(cout, sales_data_1);
  cout << "\n";

  Sales_data sales_data_2 = Sales_data("The Art of Electronics", 2, 45);
  print(cout, sales_data_2);
  cout << "\n";

  // copy paste "0-201-78345-X 3 20.00" to check
  Sales_data sales_data_3 = Sales_data(cin); 
  print(cout, sales_data_3);
  cout << "\n";

  return 0;
}