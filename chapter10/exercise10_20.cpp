// Use <count_if> to count how many words in <vector> whose length>=6 chars
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string make_plural(size_t ctr, const string& word, const string& ending) {
  return (ctr>1) ? word+ending : word;
}

void biggies(vector<string>& words, vector<string>::size_type sz) {
  auto cnt = count_if(
    words.begin(), words.end(),
    [sz](const string& str) { return str.size() >= sz; }
  );

  cout << cnt << " " << make_plural(cnt, "word", "s") << " of length " << sz << " or longer" << endl;
}

int main() {
  vector<string> words = {
    "these", "quick", "reddyish", "foxes", "jump", "over", "slowest", "turtles"
  };
  biggies(words, 6);

  return 0;
}