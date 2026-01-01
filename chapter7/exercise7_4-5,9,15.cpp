// Exercise7_4: Write a class Person that represents name & address of a person
// Exercise7_5: Provide operations in Person clas to return the name and address
// Exercise7_9: Add operations to read and print Person
#include <iostream>
#include <string>

using namespace std;

struct Person {
// friends declarations
  friend istream& read(istream&, Person& person);
  friend ostream& print(ostream&, const Person&);

public:
  // constructors
  Person() = default;
  Person(const string& _name, const string& _address):
    name(_name), address(_address) {}

  string get_name() const { return name; }
  string get_address() const { return address; }

private:
  string name;
  string address;
};

istream& read(istream& is, Person& person) {
  is >> person.name >> person.address;
  return is;
}

ostream& print(ostream& os, const Person& person) {
  os << person.get_name() << " " << person.get_address() << endl;
  return os;
}