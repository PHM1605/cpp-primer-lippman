// Write a program to read a sequence of ints from cin and store those values in a vector
// Input: typing '12 2 1 9'
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

int main() {
    vector<int> v{1,2,3,4,5,6,7,8,9};
    // square each element in vector
    for (auto &i: v) {
        i *= i;
    }
    // display squared vector
    for (auto i: v) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}