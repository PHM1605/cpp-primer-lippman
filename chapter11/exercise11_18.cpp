// Word counting program
// typing: "this is a test file to test word count what is this"
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int main() {
  map<string, size_t> word_count;
  // start reading values for <word_count>
  set<string> exclude = {"The","But","And","Or","An","A","the","but","and","or","an","a"};
  string word;
  while(cin >> word) {
    // if word not in exclude set
    if (exclude.find(word) == exclude.end()) {
      ++word_count[word];
    }
  }

  map<string,size_t>::const_iterator map_it = word_count.cbegin();
  while(map_it != word_count.cend()) {
    cout << map_it->first << " occurs " << map_it->second << " times\n";
    ++map_it;
  }

  return 0;
}