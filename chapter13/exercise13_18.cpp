// Define <Employer> class
#include <iostream>

using namespace std;

class Employer {
public:
  static size_t count;

  // constructor
  Employer(): id_number(count++) {}
  Employer(const string& employee): 
    id_number(count++), employee_name(employee) {}
  
  // copy-control. NOTE: we should NOT copy id_number
  Employer(const Employer& employer):
    id_number(count++), employee_name(employer.employee_name) {}

  Employer& operator=(const Employer& employer) {
    if (this != &employer)
      employee_name = employer.employee_name;
    return *this;
  }

  void print() {
    cout << "ID = " << id_number << ", employee name = " << employee_name << endl;
  }

private:
  int id_number;
  string employee_name;
};

size_t Employer::count = 0;

int main() {
  Employer a("Alice");
  Employer b("Bob");

  cout << "Initial objects:\n";
  a.print();
  b.print();

  cout << "Copy construction:\n";
  Employer c = a; // another "Alice" with new ID
  c.print();

  cout << "Copy assignment:\n";
  b = a;
  b.print(); // change "Bob" to "Alice" => still same ID

  return 0;
}