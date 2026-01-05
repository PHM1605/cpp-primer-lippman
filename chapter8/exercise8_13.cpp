// Phone number program
// - read from a file
// - using <ostringstream> to format output before printing out
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct PersonInfo {
  string name;
  vector<string> phones;
};

// check if a phone number is valid or not
bool valid(const string& s) {
  // phone should have 10 digits
  if (s.size() != 10) return false;
  // phone should not contain special characters
  for (char c: s) {
    if (!isdigit(c)) 
      return false;
  }
  return true;
}

// format in (xxx) xxx-xxxx format
string format(const string& s) {
  return "(" + s.substr(0,3) + ") " + s.substr(3,3) + "-" + s.substr(6);
}

int main() {
  string line, phone_num;
  vector<PersonInfo> people;

  // read list of people
  ifstream file_stream("phone_data_input.txt");
  // read file stream into each <line> (string)
  while(getline(file_stream, line)) {
    istringstream record(line);
    PersonInfo info;
    record >> info.name;
    // read each phone number from one person
    while(record >> phone_num)
      info.phones.push_back(phone_num);
    people.push_back(info);
  }

  // start reading throuhg people list
  for (const auto& entry: people) {
    // formatted: good phone-number string
    // badNums: bad phone-number-string
    ostringstream formatted, badNums;
    for (const auto& nums: entry.phones) {
      if (!valid(nums)) {
        badNums << " " << nums;
      } else {
        formatted << " " << format(nums);
      }
    }
    // if there is no bad numbers
    if (badNums.str().empty())
      cout << entry.name << " " << formatted.str() << endl;
    // if there is bad numbers
    else
      cerr << "input error: " << entry.name << " invalid number(s) " << badNums.str() << endl;
  }

  return 0;
}