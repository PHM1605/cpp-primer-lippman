// Write Account class 
// NOTE: static function CANNOT call non-static members
#include <iostream>
#include <string>

using namespace std;

class Account {
public: 
  void calculate() {
    amount += amount * interestRate;
  }
  static double rate() {
    return interestRate;
  }
  static void rate(double); // set rate

private:
  string owner;
  double amount;
  static double interestRate;
  static double initRate();

// NOTE: we can only initialize <static> with constexpr
private: 
  static constexpr int period = 30;
  double daily_tbl[period];
};
constexpr int Account::period; // definition WITHOUT VALUE

// set static members
double Account::interestRate = initRate();

// NOTE: we do NOT need <static> keyword when defining outside - function to set new rate
void Account::rate(double newRate) {
  interestRate = newRate;
}

int main() {
  Account ac1;
  Account* ac2 = &ac1;
  // we can call <static> from object or pointer to object
  cout << ac1.rate() << endl;
  cout << ac2->rate() << endl;

  return 0;
}