// Write 3 different versions of a program to print the elements of ia.
// Method 1: use range 'for' loop
// Method 2: use 'for' loop using subscript
// Method 3: use 'for' loop using pointers
// Note: use 'alias'
#include <iostream>
#include <iterator>

using std::cin;
using std::cout;
using std::endl;

using int_array = int[4];

int main() {
    int ia[3][4] = {
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {8, 9, 10, 11}
    };
    
    // Method 1: use range 'for' loop
    cout << "Use range 'for' loop: \n";
    for (int_array &row: ia) {
        for (int col: row) {
            cout << col << " ";
        }
    }
    cout << endl;

    // Method 2: use 'for' loop with subscripts
    cout << "Use 'for' loop with subscripts: \n";
    for (int i=0; i<3; ++i) {
        for (int j=0; j<4; j++) {
            cout << ia[i][j] << " ";
        }
    }
    cout << endl;

    // Method 3: use 'for' loop with pointers
    cout << "Use 'for' loop with pointers: \n";
    for (int_array *p = std::begin(ia); p < std::end(ia); ++p) {
        for (int* q = std::begin(*p); q < std::end(*p); q++) {
            cout << *q << " ";
        }
    }
    cout << endl;

    return 0;
}