// Write a program to create a vector 10 ints. Using an iterator, assign each element a value that is twice its current value. Printing vector to test
#include <iostream>
#include <vector>

using std::vector;
using std::endl;
using std::cout;

int main() {
    vector<int> vect {1,6,8,2,5,7,9,10,0,3};
    for (auto it = vect.begin(); it != vect.end(); it++) {
        (*it) = (*it) * 2;
    }
    // print
    for (auto v : vect) {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}