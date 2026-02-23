// Write <ReadString> that read from a string stream to a vector<string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class ReadString {
public:
  ReadString(istream& i=cin):
    is(i) {}
  // function operator
  vector<string> operator()() {
    vector<string> ret;
    string line;
    while (getline(is, line))
      ret.push_back(line);
    return ret;
  } 
private:
  istream& is;
};

int main() {
  cout << "\n=== Test ReadString ===\n";
  istringstream iss("first line\nsecond line\n");
  ReadString reader(iss);
  vector<string> content = reader();
  for (auto it=content.begin(); it<content.end(); it++) {
    cout << *it << endl;
  }

  return 0;
}