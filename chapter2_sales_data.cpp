//Usage: 
// g++  chapter2_sales_data.cpp
// ./a < chapter2_sales_data_input.txt
#include <iostream>
#include <string>
#include "Sales_data.h"

int main() {
    Sales_data data1, data2;
    double price = 0;
    // read the 1st transaction
    std::cin >> data1.bookNo >> data1.units_sold >> price;
    data1.revenue = data1.units_sold * price;
    // read the 2nd transaction
    std::cin >> data2.bookNo >> data2.units_sold >> price;
    data2.revenue = data2.units_sold * price;
    // compare and add only when two ISBNs the same
    if (data1.bookNo == data2.bookNo) {
        unsigned totalCnt = data1.units_sold + data2.units_sold;
        double totalRevenue = data1.revenue + data2.revenue;
        std::cout << data1.bookNo << " " << totalCnt << " " << totalRevenue << " ";
        if (totalCnt != 0) 
            std::cout << totalRevenue / totalCnt << std::endl;
        else 
            std::cout << "(no sales)" << std::endl;
        return 0;
    } else {
        std::cerr << "Data must refer to the same ISBN" << std::endl;
        return -1;
    }
}