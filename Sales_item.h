#ifndef SALESITEM_H
#define SALESITEM_H

#include <iostream>
#include <string.h>

class Sales_item {
friend std::istream& operator>>(std::istream&, Sales_item&);
friend std::ostream& operator<<(std::ostream&, Sales_item&);
friend bool operator<(const Sales_item&, const Sales_item&);
friend bool operator==(const Sales_item&, const Sales_item&);
public:
    Sales_item() = default;
    Sales_item(const std::string& book): bookNo(book) {}
    Sales_item(std::istream& is) { is >> *this; }
public:
    Sales_item& operator+=(const Sales_item&);
    // 'const' means this function doesn't change any value of this object
    std::string isbn() const { return bookNo; }
    double avg_price() const; 
private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

std::istream& operator>>(std::istream& in, Sales_item& s) {

}

#endif