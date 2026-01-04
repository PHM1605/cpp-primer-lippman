// Write a function that takes and return an istream&. The function should read the stream until it hits EOF
// insert this to test: hello world this is a test
#include <iostream>
#include <string>

using namespace std;

istream& read_istream(istream& is) {
  string segment;
  while (is >> segment) {
    cout << segment << endl;
  }
  return is;
}

int main() {
  read_istream(cin);
  return 0; 
}