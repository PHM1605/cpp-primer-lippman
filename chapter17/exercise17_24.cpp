// Write a program with FORMATTED PHONE number
#include <iostream>
#include <regex>

using namespace std;

int main() {
  // "(\\()?" means optional ("
  // "(\\d{3})" means "3 digits"
  // "(\\))?" means "optional )"
  // "([-. ])?" means "optional 1 of the 3 chars"

  // (012) 234 5678 or 012.234.5678...
  string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
  regex r(phone);
  
  // format regex match to a new format 
  string fmt = "$2.$5.$7";
  string number = "(908) 555-1800";
  cout << regex_replace(number, r, fmt) << endl; 

  return 0;
}