// Implement the word-count program
// typing: "this is a test file to test word count what is this"
// USING <unordered_map>
#include <unordered_map>
#include <iostream>

using namespace std;

int main() {
  unordered_map<string, size_t> word_count;
  string word;
  while(cin >> word)
    ++word_count[word];
  
  // print
  for (const auto& w : word_count)
    cout << w.first << " occurs " << w.second << ((w.second>1)?" times":"time") << endl;

  return 0;
}