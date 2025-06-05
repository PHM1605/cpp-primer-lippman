#include <iostream>

int main(){
    int lower_lim, upper_lim;
    std::cout << "Enter two numbers" << std::endl;
    std::cin >> lower_lim >> upper_lim;

    while(lower_lim<=upper_lim) {
        std::cout << lower_lim++ << std::endl;
    }
    return 0;
}