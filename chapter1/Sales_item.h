#ifndef SALESITEM_H
#define SALESITEM_H

#include <iostream>
#include <string.h>

class Sales_item {
friend std::istream& operator>>(std::istream&, Sales_item&);
friend std::ostream& operator<<(std::ostream&, const Sales_item&);
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

Sales_item& Sales_item::operator+= (const Sales_item& rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

Sales_item operator+(const Sales_item& lhs, const Sales_item& rhs) {
    Sales_item ret(lhs);
    ret += rhs;
    return ret;
}

std::istream& operator>>(std::istream& in, Sales_item& s) {
    double price;
    in >> s.bookNo >> s.units_sold >> price;
    // if inputs succeeded
    if (in) 
        s.revenue = s.units_sold * price;
    else 
        s = Sales_item(); // input failed: reset object to default state
    return in;
}

std::ostream& operator<<(std::ostream& out, const Sales_item& s) {
    out << s.isbn() << " " << s.units_sold << " " << s.revenue << " " << s.avg_price();
    return out;
}

double Sales_item::avg_price() const {
    if (units_sold)
        return revenue/units_sold;
    else 
        return 0;
}

#endif