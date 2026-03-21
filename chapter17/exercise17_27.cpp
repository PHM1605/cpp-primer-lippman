// Write a program that reformats a 9-digit zipcode as ddddd-dddd
#include <sstream>
#include <iostream>
#include <regex>

using namespace std;

int main() {
  string zipcode = "(\\d{5})(\\d{4})";
  regex r(zipcode);
  string my_zipcode("123456789");
  string result = regex_replace(my_zipcode, r, "$1-$2");
  cout << result << endl;

  return 0;
}