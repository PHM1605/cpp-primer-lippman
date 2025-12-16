// Convert the first paragraph in 'text' (vector of strings) to UPPERCASE. Print its contents
// Usage: g++ exercise3_22.cpp
// then: ./a.out < exercise3_22_input.txt
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

void to_uppercase(string& s) {
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
}

int main() {
    // reading file into 'text'
    vector<string> text;
    string line;
    bool in_first_paragraph = true;

    while(getline(cin, line)) {
        if (line.empty()) {
            text.push_back("");
            in_first_paragraph = false;
            continue;
        }
        std::stringstream ss(line);
        string sentence;
        while(getline(ss, sentence, '.')) {
            if (!sentence.empty()) {
                if (in_first_paragraph) 
                    to_uppercase(sentence);
                text.push_back(sentence);
            }            
        }
        in_first_paragraph = false;
    }

    for (const auto& s: text) {
        if (s.empty()) 
            cout << "[PARA BREAK]" << endl;
        else 
            cout  << "[SENTENCE] " << s << endl;
    }
    
    return 0;
}