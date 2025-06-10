#include <iostream>
#include <string>

int main(){
    std::string word;
    std::cout << "Enter words (Ctrl+D to end on Unix, Ctrl+Z on Windows):\n";
    while(std::cin>>word) {
        std::cout << "Read word: " << word << std::endl;
    }
    return 0;
}