// Write a program to concatenate 2 string literals; put result in a dynamically allocated array of <char>
#include <iostream>
#include <cstring>

using namespace std;

int main() {
  const char* s1 = "Hello, ";
  const char* s2 = "World!";

  // +1 for \0
  size_t len = strlen(s1) + strlen(s2) + 1;
  char* result = new char[len];
  
  // copy and concatenate
  strcpy(result, s1);
  strcat(result, s2);

  // print
  cout << result << endl;

  // cleanup
  delete[] result;
  return 0;
}