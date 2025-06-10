#include <iostream>
#include <string>

int main(){
    std::string line;
    std::cout << "Enter lines (Ctrl+D to end on Unix, Ctrl+Z on Windows):\n";
    while(getline(std::cin, line)) {
        std::cout << "Read line: " << line << std::endl;
    }
    return 0;
}