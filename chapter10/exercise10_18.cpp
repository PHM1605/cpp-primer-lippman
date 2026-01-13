// Partition a vector of words, print words with >=5 chars WITH 5 IS A PARAMETER => using Lambda
// - using <partition> instead of <find_if>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void elimDups(vector<string>& words) {
  sort(words.begin(), words.end());
  // put unique at start; duplicated at end; return iterators after 1st part
  auto end_unique = unique(words.begin(), words.end());
  // remove duplicated
  words.erase(end_unique, words.end());
}

// make "word" => "words" if plural
string make_plural(size_t ctr, const string& word, const string& ending) {
  return (ctr > 1) ? word+ending : word;
}

void biggies(vector<string>& words, vector<string>::size_type sz) {
  // put words in alphabetical order and remove duplicates
  elimDups(words);
  // sort by length; maintain alphabetical order USING LAMBDA
  stable_sort(
    words.begin(), words.end(), 
    [](const string& a, const string& b) {
      return a.size() < b.size();
    }
  );
  // 1st part: True with that predicate; 2nd part: False with that predicate
  // return => pointer ONE-PASS the 1st part
  auto wc = partition(
    words.begin(), words.end(),
    [sz](const string& input_str) {
      return input_str.size() >= sz;
    }
  );

  // count number of elements with >=5 chars
  auto count = wc - words.begin();
  cout << count << " " << make_plural(count, "word", "s") << " of length " << sz << " or longer" << endl;
  // print >=5 chars words with <for_each> which uses Lambda too
  for_each(
    words.begin(), wc,
    [](const string& s) {
      cout << s << " ";
    }
  );
  cout << endl;
}

int main() {
  vector<string> words = {
    "the", "quick", "red", "fox", "jumps", "over", "slow", "turtle"
  };
  biggies(words, 5);

  return 0;
}