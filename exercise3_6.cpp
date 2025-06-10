// Use a range 'for' to change all the characters in a string to 'X'
#include <iostream>
#include <string>

int main() {
    std::string s("This is a test string");

    for (char &c: s) {
        c = 'X';
    }
    std::cout << s << std::endl;
    return 0;
}