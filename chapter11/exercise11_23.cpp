// Write the "family-tree" program using multimap<string, vector<string>> 
// - key=<family-name>
// - mapped=<vector-of-first-names>
#include <iostream>
#include <map>
#include <vector>

using namespace std;



int main() {
  multimap<string, vector<string>> families;
  families.insert({"Smith", {"Jone", "Emily"}});
  families.insert({"Smith", {"Test"}});
  families.insert({"Nguyen", {"Mai","Lan","Trinh"}});

  // Try the <erase> operation
  // cout << families.erase("Smith") << endl;

  // print
  for (auto& family: families) {
    cout << family.first << ": \n";
    for (auto& member: family.second) {
      cout << "- " << member << endl;
    }
  }

  return 0;
}