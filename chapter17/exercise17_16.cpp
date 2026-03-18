// Write a program that finds TERM (not entire word) violating the English spelling rule
// "i must be before e except after c"
#include <regex>
#include <iostream>

using namespace std;

int main() {
  // violated pattern: any character outside "c" before "ei"
  string pattern("[^c]ei");

  regex r(pattern);
  smatch results; // object holds the result of a match
  string test_str = "receipt freind theif receive";
  // begin the regex search => return 1st match word
  if (regex_search(test_str, results, r))
    cout << results.str() << endl;

  return 0;
}