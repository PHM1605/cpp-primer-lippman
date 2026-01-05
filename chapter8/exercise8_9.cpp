// print the content of <istringstream> object
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

void print_stream(istringstream& iss) {
  string segment;
  while(iss >> segment) {
    cout << segment << endl;
  }
}

int main() {
  istringstream iss("This is a test string");
  print_stream(iss);
  return 0;
}