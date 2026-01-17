// define map<string,vector<int>> and illustrate <find>
#include <map>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  map<string,vector<int>> m;
  m.insert({"apple", {1,5,3}});
  m.insert({"orange", {2,3}});
  m.insert({"melon", {2,6,7,8,1}});

  // try <find>
  auto iter = m.find("orange");

  // print
  cout << "item: " << iter->first << endl;
  cout << "sold: ";
  for (auto i: iter->second) {
    cout << i << " ";
  }
  cout << endl;
  return 0;
}