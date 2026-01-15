// Word counting program. Using <map> and <set>
// typing: "This is a test file to test word count. What is this?"
#include <set>
#include <map>
#include <iostream>

using namespace std;

int main() {
  map<string, size_t> word_count;
  set<string> exclude = {"The","But","And","Or","An","A","the","but","and","or","an","a"};
  string word;
  while(cin>>word) {
    // only count words that are NOT in the <exclude> set
    if (exclude.find(word) == exclude.end()) {
      ++word_count[word];
    }
  }
  
  // print
  for(const auto& w: word_count) {
    cout << w.first << " occurs " << w.second << ((w.second>1) ? " times" : " time") << endl;
  }

  return 0;
}