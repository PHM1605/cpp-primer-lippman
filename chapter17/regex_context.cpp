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
     // it->prefix(): the part BEFORE matched word
    auto pos = it->prefix().length();
    pos = pos>10 ? pos-10 : 0;
    cout << it->prefix().str().substr(pos) // last part of prefix
      << "\n\t\t>>> " << it->str() << " <<<\n" // matched word
      << it->suffix().str().substr(0,10) << endl;
  }
  
  return 0;
}