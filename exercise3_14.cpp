// Write a program to read a sequence of ints from cin and store those values in a vector
// Input: typing '12 2 1 9'
#include <iostream>
#include <vector>

using std::vector;

int main() {
    int num;
    vector<int> nums;
    while (std::cin >> num) {
        nums.push_back(num);
    }
    // print the input vector
    for (auto val: nums)
        std::cout << val << std::endl; 
    return 0;
}