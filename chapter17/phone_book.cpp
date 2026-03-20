// Reformat phone book to a consistent format
#include <iostream>
#include <fstream>
#include<regex>

using namespace std;

int main() {
  string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)?(\\d{4})";
  regex r(phone);
  smatch m;
  string s;

  ifstream infile("phone_book_input.txt");

  // to reformat output
  string fmt = "$2.$5.$7";
  while(getline(infile, s)) {
    cout << regex_replace(s, r, fmt) << endl;
  }
  
  return 0;
}