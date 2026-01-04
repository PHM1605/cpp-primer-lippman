#pragma once 
#include <iostream>
#include <string>

using namespace std;

class Sales_data {
// outer class friend define
friend Sales_data add(const Sales_data&, const Sales_data&);
friend istream& read(istream&, Sales_data&);
friend ostream& print(ostream&, const Sales_data&);

public:
    // constructor
    Sales_data() = default;
    Sales_data(const string &s): bookNo(s) {}
    explicit Sales_data(const string &s, unsigned n, double p): bookNo(s), units_sold(n), revenue(p*n) {}
    explicit Sales_data(istream &);
    
    // operations 
    string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data&);

private:
    inline double avg_price() const { return units_sold ? revenue/units_sold : 0; }
    // data members
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

// non member functions to interact with Sales_data
Sales_data add(const Sales_data&, const Sales_data&);
ostream& print(ostream&, const Sales_data&);
istream& read(istream&, Sales_data&);