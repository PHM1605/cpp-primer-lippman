#pragma once 
#include <string>

using namespace std;

struct Sales_data {
    // new members
    string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data&);
    double avg_price() const;

    // data members
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

// non member functions to interact with Sales_data
Sales_data add(const Sales_data&, const Sales_data&);
ostream& print(ostream&, const Sales_data&);
istream& read(istream&, Sales_data&);