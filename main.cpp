#include <iostream>
#include "Sales_item.h"

int main(){
    Sales_item total;
    if (std::cin >> total) {

    } else {
        std::cerr << "Data must refer to the same ISBN" << std::endl;
        return -1;
    }
}