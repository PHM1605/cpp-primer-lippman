// Write a program that reads a string and remove its punctuation
#include <iostream>
#include <string>

int main() {
    std::string s("Test!!! Whatever.");
    std::string ret;
    for (auto c: s) {
        if (!ispunct(c)) ret.push_back(c);
    }
    std::cout << ret << std::endl;
    return 0;
}