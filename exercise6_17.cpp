#include <iostream>
#include <cctype>
#include <string>

using namespace std;

bool hasCapital(const string& s) {
  for (char c: s) {
    if (isupper(c)) {
      return true;
    }
  }
  return false;
}

void toLower(string& s) {
  for (char& c: s) {
    c = tolower(c);
  }
}


int main() {
  string text = "This is a test string";

  // Test capital
  if (hasCapital(text)) {
    cout << "The string has capital letter(s)\n";
  } else {
    cout << "The string has NO capital letter(s)\n";
  }

  // Test toLower
  toLower(text);
  cout << "Lower case version: " << text << endl;

  return 0;
}