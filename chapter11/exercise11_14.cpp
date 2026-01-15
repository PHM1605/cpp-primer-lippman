// Define a <map> of "<last-name>: vector<x>"" with x is a <pair> of name:birthday
// Write code to 1/ add new family and 2/ add new children
#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

int main() {
  map<string, vector<pair<string,string>>> families;
  // method 1: add a family; then add children
  families["Smith"] = vector<pair<string,string>>{};
  families["Smith"].push_back(make_pair("John","1/1/2000"));
  families["Smith"].push_back(make_pair("Emily","2/2/2000"));
  // method 2: add family and children at once
  families["Nguyen"].push_back(make_pair("Mai","4/4/2001"));
  families["Nguyen"].push_back(make_pair("Lan","5/5/2002"));
  // method 3: use <insert> all at once
  families.insert({"Brown", {{"Tom","6/6/2003"}, {"Lucy", "7/7/2004"}}});

  //print
  for (const auto& pr: families) {
    cout << pr.first << ":\n";
    for (const auto& child: pr.second)
      cout << "name " << child.first << " with birthday " << child.second << endl;
    cout << endl;
  }

  return 0;
}