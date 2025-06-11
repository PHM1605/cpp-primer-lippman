#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::endl;

int main() {
    vector<string> text {"abc", "def", "deh", "xyz"};
    string sought = "deh";
    auto beg = text.begin();
    auto zero_loc = text.begin();
    auto end = text.end();
    auto mid = text.begin() + (end-beg)/2; // notice: iterator only supports 'subtraction', not 'addition of iterators'
    while (mid != end && *mid != sought) {
        if (sought < *mid) end = mid;
        else beg = mid+1;
        mid = beg + (end-beg)/2;
    }
    if (mid == end) {
        cout << "That string is not found in vectors\n";
    } else if (*mid == sought) {
        cout << "String " << sought << " is at index " << (mid-zero_loc) << endl;
    }
    return 0;
}