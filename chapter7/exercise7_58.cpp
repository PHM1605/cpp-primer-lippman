// which, if any static data member declarations wrong? 
#include <vector>
#include <iostream>
using namespace std;

class Example 
{ 
public: 
  // WRONG: static double rate=6.5; static cannot be initialized inside without <constexpr>
  static constexpr double rate = 6.5;  
  static const int vecSize = 20; 
  static vector<double> vec;
};

vector<double> Example::vec(Example::vecSize);