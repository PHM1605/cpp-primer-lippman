// Use <bind> and <check_size> to 1st element in vector<int> that has value > len(string)
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;
using namespace std::placeholders;

bool check_size(const string& s, string::size_type sz) {
  return sz > s.size(); 
}

// bind: to convert 2-param function to 1-param function
int main() {
  vector<int> vi = {1,3,5,7,9};
  string s = "hello"; // length = 5
  auto iter = find_if(
    vi.begin(), vi.end(),
    bind(check_size, s, _1)
  );

  if (iter != vi.end())
    cout << *iter << endl;

  return 0;
}