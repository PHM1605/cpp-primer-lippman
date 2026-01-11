// Write a class to handle DATE
#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

class Date {
public:
  Date() = default;
  Date(const string& s) {
    // handle 1/1/1999
    if (s.find('/') != string::npos) {
      char slash;
      stringstream ss(s);
      ss >> day >> slash >> month >> slash >> year;
    }
    // handle "January 1,1990" or Jan 1, 1990
    else {
      static map<string, int> months = {
        {"Jan",1}, {"January",1},
        {"Feb",2}, {"February",2},
        {"Mar",3}, {"March",3},
        {"Apr",4}, {"April",4},
        {"May",5}, {"May",5},
        {"Jun",6}, {"June",6},
        {"Jul",7}, {"July",7},
        {"Aug",8}, {"August",8},
        {"Sep",9}, {"September",9},
        {"Oct",10}, {"October",10},
        {"Nov",11}, {"November",11},
        {"Dec",12}, {"December",12},
      };
      char comma;
      string monthStr;
      stringstream ss(s);
      ss >> monthStr >> day >> comma >> year;
      month = months[monthStr];
    }
  }

  void print() {
    cout << day << "/" << month << "/" << year << endl;
  }

private:
  unsigned int year = 0;
  unsigned int month = 0;
  unsigned int day = 0;
};

int main() {
  Date d1("January 1, 1990");
  Date d2("1/1/1990");
  Date d3("Jan 1, 1990");

  d1.print();
  d2.print();
  d3.print();

  return 0;
}