// Write phone-book program that prints the 1st phone number for each person
#include <iostream>
#include <regex>
#include <fstream>

using namespace std;

int main() {
  string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";
  regex r(phone);
  smatch m;
  string s;

  ifstream infile("phone_book_input.txt");
  // format of output
  string fmt = "$2.$5.$7";
  while(getline(infile, s)) {
    // NOTE: ONLY the 1st match
    if (regex_search(s, m, r)) {
      cout << m.format(fmt) << endl;
    } else {
      cout << "no phone" << endl;
    }
  }

  return 0;
}