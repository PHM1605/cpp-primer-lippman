// Write a program to process a vector<string> whose elements represent <int> values => calculate sum
// Write a program to process a vector<string> whose elements represent <double> values => calculate sum
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
  vector<string> vs {"1", "12", "4", "7"};
  int sum_int = 0;
  for (auto& s : vs) {
    sum_int += stoi(s);
  }
  cout << sum_int << endl;

  vector<string> vs2 {"1.2", "2.3", "1"};
  double sum_double = 0.0f;
  for(auto& s: vs2) {
    sum_double += stod(s);
  }
  cout << sum_double << endl;
  return 0;
}