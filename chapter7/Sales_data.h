#pragma once 
#include <iostream>
#include <string>

using namespace std;

struct Sales_data {
    // constructor
    Sales_data() = default;
    Sales_data(const string &s): bookNo(s) {}
    Sales_data(const string &s, unsigned n, double p): bookNo(s), units_sold(n), revenue(p*n) {}
    Sales_data(istream &);
    
    // operations 
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