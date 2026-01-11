// Use the <count> strings function
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main() {
  vector<string> vs = {"This","is","a","test","and","test"};
  string val = "test";
  auto result = count(vs.begin(), vs.end(), val);
  cout << result << endl;
  return 0;
}