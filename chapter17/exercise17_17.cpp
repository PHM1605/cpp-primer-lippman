// Write program to find all words that violates the rule
// "'i' must be before 'e' except when the prior char is 'c'"
// NOTE: we have a list of exceptions e.g. "albeit"...
#include <iostream>
#include <regex>
#include <set>

using namespace std;

int main() {
  // violated pattern
  string pattern("[^c]ei");
  pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";

  // exceptions
  set<string> exceptions = {
    "albeit","neighbor","weird","their","foreign","height","either","neither"
  };

  string file = "receipt freind theif receive albeit neighbor weird height";
  // ignore case during the match
  regex r(pattern, regex::icase);
  // search for all matches
  for(sregex_iterator it(file.begin(), file.end(), r), end_it; it!=end_it; ++it) {
    string word = it->str();
    // normalize to lowercase for comparison
    string lower = word;
    for(auto &c: lower)
      c = tolower(c);
    // if word not in exception set
    if (exceptions.find(lower) == exceptions.end())
      cout << word << endl;
  }

  return 0;
}