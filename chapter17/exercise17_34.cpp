// Write tests on IO-manipulator
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
  // boolalpha: display boolean as "true"/"false" instead of 1/0
   cout << "default bool values: " << true << " " << false
    << "\nalpha bool values: " << boolalpha << true << " " << false << endl;
    // noboolalpha: reset to default
  bool bool_val = false;
  cout << boolalpha << bool_val << noboolalpha << "; after: " << bool_val << endl; // print <bool_val> with <string>-format; then reset

  // oct, hex, dec: change notation base format
  cout << "\ndefault: " << 20 << " " << 1024 << endl;
  cout << "octal: " << oct << 20 << " " << 1024 << endl;
  cout << "hex: " << hex << 20 << " " << 1024 << endl;
  cout << "decimal: " << dec << 20 << " " << 1024 << endl;

  // showbase/noshowbase: enable/disable display of "notation base" of numbers
  cout << showbase;
  cout << "\ndefault: " << 20 << " " << 1024 << endl;
  cout << "octal: " << oct << 20 << " " << 1024 << endl;
  cout << "hex: " << hex << 20 << " " << 1024 << endl;
  cout << "decimal: " << dec << 20 << " " << 1024 << endl;
  cout << noshowbase; // reset

  // uppercase/nouppercase: enable/disable the display of "capital notation base"
  cout << uppercase << showbase << hex
    << "\nprinted in hexadecimal: " << 20 << " " << 1024
    << nouppercase << noshowbase << dec << endl; // reset

  // precision(), setprecision(): get or set precision value of a float
  size_t default_prec = cout.precision();
  cout << "\nPrecision: " << default_prec << ", Value: " << sqrt(2.0) << endl;
  // change default precision to 12
  cout.precision(12);
  cout << "Precision: " << cout.precision() << ", Value: " << sqrt(2.0) << endl;
  // set precision to 3 using MANIPULATOR instead of calling cout.precision()
  cout << setprecision(3);
  cout << "Precision: " << cout.precision() << ", Value: " << sqrt(2.0) << endl;
  // reset to default
  cout << setprecision(default_prec);

  // scientific, fixed, hexfloat: specify notation LOOK of float
  cout << "\ndefault format: " << 100*sqrt(2.0) << endl; // default: 6-digit before AND after the '.'
  // now 6-digit precision is for ONLY AFTER the '.'
  cout << "scientific: " << scientific << 100*sqrt(2.0) << endl
    << "fixed decimal: " << fixed << 100*sqrt(2.0) << endl
    << "hexadecimal: " << hexfloat << 100*sqrt(2.0) << endl 
    << "usedefaults: " << defaultfloat << 100*sqrt(2.0) << endl; // reset => 6-digit before AND after the '.'

  // showpoint/noshowpoint: should be print e.g. 23.0 or 23 only
  cout << endl << 10.0 << endl;
  cout << showpoint << 10.0
    << noshowpoint << endl; // reset

  return 0;
}