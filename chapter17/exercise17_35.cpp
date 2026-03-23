// Print 100*sqrt(2) with different CAPITAL format
#include<iostream>
#include <cmath>

using namespace std;

int main() {
  cout << "default format: " << 100*sqrt(2.0) << endl 
    << "scientific: " << scientific << 100*sqrt(2.0) << endl 
    << "fixed decimal: " << fixed << 100*sqrt(2.0) << endl 
    << "hexadecimal: " << hexfloat << uppercase << 100*sqrt(2.0) << endl // NOTE: UPPER HERE
    << "usedefaults: " << defaultfloat << 100*sqrt(2.0) << endl << endl;
    
  return 0;
}