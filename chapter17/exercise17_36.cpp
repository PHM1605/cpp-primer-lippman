// Print 100*sqrt(2) with right-aligned column
#include<iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
  cout << setw(20) << left << "default format: " << setw(20) << 100*sqrt(2.0) << endl 
    << setw(20) << left << "scientific: " << setw(20) << scientific << 100*sqrt(2.0) << endl 
    << setw(20) << left << "fixed decimal: " << setw(20) << fixed << 100*sqrt(2.0) << endl 
    << setw(20) << left << "hexadecimal: " << setw(20) << hexfloat << 100*sqrt(2.0) << endl
    << setw(20) << left << "usedefaults: " << setw(20) << defaultfloat << 100*sqrt(2.0) << endl << endl;
    
  return 0;
}