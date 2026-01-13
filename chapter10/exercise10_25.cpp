// <partition> a vector of words, print words with >=5 chars
// Using <check_size> and <bind>
#include <iostream>
#include <vector>
#include <functional> // for "bind"
#include <sstream>
#include <string>

using namespace std;
using namespace std::placeholders;

void elimDups(vector<string>& words) {
  sort(words.begin(), words.end()); 
  // put unique words at start; duplicated words at end
  // return pointer to end of 1st-part
  auto end_unique = unique(words.begin(), words.end());
  // remove duplicates
  words.erase(end_unique, words.end());
}

// predicate for "stable_sort"
bool isShorter(const string& s1, const string& s2) {
  return s1.size() < s2.size();
}
// predicate for "partition"
bool check_size(const string& s, vector<string>::size_type sz) {
  return s.size() >= sz;
}
// predicate for "for_each"
void print_element(const string& s) {
  cout << s << " ";
}

string make_plural(size_t ctr, const string& word, const string& ending) {
  return (ctr>1) ? word+ending : word;
}

void biggies(vector<string>& words, vector<string>::size_type sz) {
  // eliminate duplicated words in vector
  elimDups(words);
  // sort by length from short->long; maintain alphabetical order
  stable_sort(
    words.begin(), words.end(),
    isShorter
  );
  // 1st part: True with that predicate; 2nd part: False with that predicate
  // return => pointer ONE-PASS the 1st part
  auto iter = partition(
    words.begin(), words.end(),
    bind(check_size, _1, sz)
  );
  // count number of elements with >= 5 chars
  auto count = iter - words.begin();
  cout << count << " " << make_plural(count, "word", "s") << " of length " << sz << " or longer" << endl;
  for_each(
    words.begin(), iter,
    print_element
  );
  cout << endl;
}

int main() {
  stringstream ss ("the quick red fox jumps over the slow red turtle");
  string word;
  vector<string> words;
  while(ss >> word) {
    words.push_back(word);
  }

  biggies(words, 5);

  return 0;
}
