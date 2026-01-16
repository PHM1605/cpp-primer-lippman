// Using <map> iterator, write expression that assign a value to an element
#include <map>
#include <string>
#include <iostream>

using namespace std;

int main() {
  map<string, int> m = {{"apple",1}, {"banana",2}};
  // Change value of an element
  auto it = m.find("banana");
  if (it != m.end()) {
    it->second = 42;
  }
  // print
  for (auto it=m.begin(); it != m.end(); it++){
    cout << it->first << " => " << it->second << endl;
  }

  return 0;
}