// Read words from 'cin' and store in 'vector'; change to uppercase and print vector out
// Input: typing 'This is a test string'
// Output: 0 0 0 1 1 0 2 3 2 4 1
#include <iostream>
#include <vector>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;

int main() {
    vector<string> words;
    string word;
    while (cin>>word) {
        words.push_back(word);
    }
    // convert all words in vector to upper case 
    for (auto &word : words) {
        for (auto &c: word)
            c = toupper(c);
    }
    // display the vector of strings 
    for (auto word: words) {
        cout << word << " ";
    }
    cout << endl;
    return 0;
}