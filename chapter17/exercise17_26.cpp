// Write phone-book program that prints the latter phone numbers (exclude the 1st) for each person
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
    sregex_iterator it(s.begin(), s.end(), r);
    sregex_iterator end_it;
    // skip the 1st match
    if (it!=end_it) ++it;
    // print remaining matches
    for (; it!=end_it; ++it) {
      cout << it->format(fmt) << " ";
    }
    cout << endl;
  }

  return 0;
}