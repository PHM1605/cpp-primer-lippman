// Write tests on IO-manipulator
#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>

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

  // setbase: set base 8,10 or 16 only
  cout << "\nsetbase(8): " << setbase(8) << 20 << " " << 1024 << endl;
  cout << "setbase(16): " << setbase(16) << 20 << " " << 1024 << endl;
  cout << "setbase(10): " << setbase(10) << 20 << " " << 1024 << endl;  

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

  // setw: space of the next column
  // left/right: justify in the next column
  // internal: for negative number => '-' sign on the left, number on the right
  // setfill: fill column with which special character
  int i = -16;
  double d = 3.14159;
  // check padding
  cout << "\ni: " << setw(12) << i << "next col\n"
    << "d: " << setw(12) << d << "next col\n";
  // padding & left justify & reset to right justify
  cout << left 
    << "i: " << setw(12) << i << "next col\n"
    << "d: " << setw(12) << d << "next col\n"
    << right; // reset
  // put '-' to left; digits to right for negative numbers
  cout << internal 
    << "i: " << setw(12) << i << "next col\n"
    << "d: " << setw(12) << d << "next col\n";
  // padding with '#' char
  cout << setfill('#')
    << "i: " << setw(12) << i << "next col\n"
    << "d: " << setw(12) << d << "next col\n"
    << setfill(' '); // reset to default gapfiller

  // noskipws: read whitespaces in input streams too
  // skipws: reset to default
  istringstream iss1("a b     c\nd");
  char ch;
  cout << "\nWith skip whitespaces:\n";
  while(iss1 >> ch) {
    cout << ch;
  }
  istringstream iss2("a b     c\nd");
  cout << "\nWithout skip whitespaces:\n";
  iss2 >> noskipws; // set skip-whitespace of "in-stream"
  while(iss2 >> ch) {
    cout << ch;
  }
  cin >> skipws; // reset

  // showpos/noshowpos: show '+' sign for positive numbers
  cout << "\n\nshowpos: " << showpos << 42 << " " << -42 << " " << 0 << endl;
  cout << "noshowpos: " << noshowpos << 42 << " " << -42 << " " << 0 << endl;

  // unitbuf/nounitbuf: flush buffer IMMEDIATELY after every "cout" (no waiting for \n)
  cout << unitbuf;
  cout << "\nunitbuf on: each of these is flushed immediately\n";
  cout << "line1\n";
  cout << "line2\n";
  cout << nounitbuf; //reset

  // flush: manually flush the buffer once
  cout << "\nflushing now" << flush; // flush to screen WITHOUT \n 
  cout << " <- no newline before this flush\n";

  // ends: inserts a \0 into a stream
  ostringstream oss;
  oss << "hello" << ends << "world"; // "hello\0world"
  string s = oss.str(); // keep ALL string but will not print after "\0"
  cout << "\n'ends' test: original string has size " << s.size() << " but print: " << s.c_str() << endl;

  return 0;
}