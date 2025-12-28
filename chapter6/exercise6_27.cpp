// Write a function that takes an "initializer_list<int>" and produce the sum
#include <iostream>

using namespace std;

int sum_of_ints(initializer_list<int> numbers) {
  int ret = 0;
  for (auto beg=numbers.begin(); beg!=numbers.end(); ++beg) {
    ret += (*beg);
  }
  return ret;
}

int main() {
  initializer_list<int> list_to_sum({3,4,2});
  int res_sum = sum_of_ints(list_to_sum);
  cout << "Result: " << res_sum << endl;

  return 0;
}