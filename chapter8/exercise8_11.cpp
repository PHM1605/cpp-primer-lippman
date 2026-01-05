// Phone book application
// file format: <name> <phone_number_1> <phone_number_2>....
// => copy data from phone_data_input.txt to run
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct PersonInfo {
  string name;
  vector<string> phones;
};

int main() {
  string line, word; 
  vector<PersonInfo> people;

  istringstream record;
  while (getline(cin, line)) {
    PersonInfo info;
    record.clear(); // to reset the state to "good"
    record.str(line); // record with data="morgan 2015552368 8625550123", ...
    
    record >> info.name;
    while(record >> word)
      info.phones.push_back(word); 
    people.push_back(info);
  }

  // print to check
  cout << "Debug print:\n";
  for (auto& person : people) {
    cout << person.name << " ";
    for (auto& phone: person.phones) {
      cout << phone << " ";
    }
    cout << endl;
  }

  return 0;
}