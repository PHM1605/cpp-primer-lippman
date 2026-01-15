// Write a program to read a sequence of strings and ints
// storing each into a <pair>
// store all pairs in vector<>
// check: "apple 3 banana 5 orange 2"
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main() {
  vector<pair<string,int>> data;
  string s;
  int n;
  while(cin >> s >> n) {
    data.push_back(make_pair(s,n));
  }

  // print
  for (auto& p: data) {
    cout << p.first << " : " << p.second << endl;
  }

  return 0;
}