// Define a <map> of "<last-name>: vector<string> of children names"
// Write code to 1/ add new family and 2/ add new children
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
  map<string, vector<string>> families;
  // method 1: add a family; then add children
  families["Smith"] = vector<string>{};
  families["Smith"].push_back("John");
  families["Smith"].push_back("Emily");
  // method 2: add family and children at once
  families["Nguyen"].push_back("Mai");
  families["Nguyen"].push_back("Lan");
  // method 3: use <insert> all at once
  families.insert({"Brown", {"Tom", "Lucy"}});

  //print
  for (const auto& pr: families) {
    cout << pr.first << ": ";
    for (const auto& child: pr.second)
      cout << child << " ";
    cout << endl;
  }

  return 0;
}