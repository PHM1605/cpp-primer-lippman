// Write a program using conditional operator to find the elements in vector<int> that have odd value; then double it's value
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

int main () {
    vector<int> vects = {1, 10, 5, 2, 4};
    for(auto &v: vects) {
        v = ( v%2 != 0 ? v*2 : v);
        cout << v << " ";
    }
    cout << endl;

    return 0;
}