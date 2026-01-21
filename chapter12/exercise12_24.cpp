// Write a program to read a string from <cin> to a dynamically allocated array
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main() {
  string line;
  getline(cin, line);
  char* buffer = new char[line.size() + 1]; // +1 for \0
  strcpy(buffer, line.c_str());

  cout << buffer << endl;

  return 0;
}