// Convert the first paragraph in 'text' (vector of strings) to UPPERCASE. Print its contents
// Usage: g++ exercise3_22.cpp
// then: ./a.out < exercise3_22_input.txt
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

int main() {
    string word;
    // reading file into 'text'
    vector<string> text;
    while(cin >> word) {
        text.push_back(word);
    }
    
    return 0;
}