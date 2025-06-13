// Histogram of student grades, bin-size of 10 (the perfect grade 100 is one group)
// Input: typing '42 65 95 100 39 67 95 76 88 76 83 92 76 93'
// Output: 0 0 0 1 1 0 2 3 2 4 1
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
    unsigned scores[11] = {};
    unsigned grade;
    while(cin >> grade) {
        if (grade <= 100) 
            ++scores[grade/10];
    }
    // display the histogram
    
    return 0;
}