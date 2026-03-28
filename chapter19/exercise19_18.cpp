// Count numper of empty strings in vector
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

int main() {
  vector<string> words = {"hello", "", "world", "", "C++"};

  size_t count = count_if(words.begin(), words.end(), mem_fn(&string::empty));

  cout << "Number of empty strings: " << count << endl;
  return 0;
}