// Read a set of integers to a vector, print the sum of each pair of adjacent elements
// Input: 2 3 5 1 7
// Sum of each pair: 5 8 6 8
// Output2: 9 4
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

void print_vec(vector<int> vect) {
    for (auto v: vect) {
        cout << v << " ";
    }
    cout << endl;
}

int main() {
    int num, len=0;
    vector<int> numbers;
    while(cin>>num) {
        numbers.push_back(num);
        len++;
    }
    // Print sum of each pair
    vector<int> sum_pair;
    for (unsigned i=1; i<len; i++) {
        sum_pair.push_back(numbers[i-1] + numbers[i]);
    }
    cout << "Sum of each pair: ";
    print_vec(sum_pair);

    // Print first and last sum
    int halfway_idx = len/2;
    vector<int> sum_first_last;
    for (int i=0; i<halfway_idx; i++) {
        sum_first_last.push_back(numbers[i] + numbers[len-1-i]);
    }
    cout << "Sum of first and last: ";
    print_vec(sum_first_last);

    return 0;
}