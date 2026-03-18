// find all words matching a regex in a long text
// print the CONTEXT as well
#include <iostream>
#include <regex>

using namespace std;

int main() {
  string file =
    "This is a simple receipt example. "
    "My freind made a mistake. "
    "Another theif was caught nearby. "
    "But receive and neighbor are correct words.";

  // regex: words containing "ei" not after "c"
  string pattern("[^c]ei");
  pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
  regex r(pattern, regex::icase);

  for (sregex_iterator it(file.begin(), file.end(), r), end_it; it!=end_it; ++it) {
     
  }
  
  return 0;
}