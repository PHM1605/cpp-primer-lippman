// Write <biggies> program using function-object
// find words that has >= num-chars
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print_vect(vector<string>& words){
  for (auto& word: words) {
    cout << word << " ";
  }
  cout << endl;
}

// put words in alphabetical order and remove dups
void elimDups(vector<string>& words) {
  sort(words.begin(), words.end());
  // put unique at start; dups at end; return <iter> after 1st-part
  auto end_unique = unique(words.begin(), words.end());
  // remove dups
  words.erase(end_unique, words.end());
}

class IsShorter {
public:
  bool operator()(const string& a, const string& b) {
    return a.size() < b.size();
  }
};

class IsLonger {
public:
  IsLonger(size_t val): ref_val(val) {}
  bool operator()(const string& s) {
    return s.size() >= ref_val;
  }
private:
  size_t ref_val;
};

class PrintString {
public:
  void operator()(const string& s) {
    cout << s << " ";
  }
};

void biggies(vector<string>& words, size_t sz) {
  elimDups(words);
  // sort by length; keep alphabetical order, using <IsShorter> object
  stable_sort(
    words.begin(), words.end(),
    IsShorter()
  );
  cout << "After sort and remove dups: ";
  print_vect(words);
  // find iterator to 1st element in <words> that has at least <sz> chars
  auto wc = find_if(
    words.begin(), words.end(),
    IsLonger(sz)
  );
  // count number of elements >=5 chars
  auto count = words.end() - wc;
  cout << count << " " << (count>1 ? "words": "word") << " of length " << sz << " or longer\n";
  // print >=5 chars words
  for_each(wc, words.end(), PrintString());
  cout << endl;
}

int main() {
  vector<string> words = {"hello", "world", "we", "say", "hello", "again"};
  biggies(words, 5);
  
  return 0;
}