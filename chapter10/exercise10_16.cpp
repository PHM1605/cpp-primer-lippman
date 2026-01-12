// Partition a vector of words, print words with >=5 chars WITH 5 IS A PARAMETER => using Lambda
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// NOTE: <partition> only use ONE PARAMETERS, so we must hard code "5" here
bool has_5_chars(const string& input_str) {
  return input_str.size() >= 5;
}

int main() {
  vector<string> words = {
    "the", "quick", "red", "fox", "jumps", "over", "slow", "turtle"
  };
  // this iterator is after-1st-partition
  auto it = partition(words.begin(), words.end(), has_5_chars);

  // debug print
  for (auto iter = words.begin(); iter != it; ++iter) {
    cout << *iter << " ";
  }
  cout << endl;

  return 0;
}