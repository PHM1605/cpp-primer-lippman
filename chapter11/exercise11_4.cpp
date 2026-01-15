// Word counting program. Using <map> and <set>
// EXTENSION: "Example example example." should count as 1 key and value of 3
#include <set>
#include <map>
#include <iostream>
#include <cctype> // for <ispunct> and <tolower>

using namespace std;

int main() {
  map<string, size_t> word_count;
  set<string> exclude = {"the","but","and","or","an","a"};
  string word;
  while(cin>>word) {
    // modify word
    for (auto iter = word.begin(); iter != word.end(); ) {
      // delete '.', '?', ... chars
      if (ispunct(*iter))
        iter = word.erase(iter);
      // convert all to lower
      else {
        *iter = tolower(*iter);
        iter++;
      } 
    }
    // only count words that are NOT in the <exclude> set; remove empty words (i.e. from punctuation)
    if (!word.empty() && exclude.find(word) == exclude.end()) {
      ++word_count[word];
    }
  }
  
  // print
  for(const auto& w: word_count) {
    cout << w.first << " occurs " << w.second << ((w.second>1) ? " times" : " time") << endl;
  }

  return 0;
}