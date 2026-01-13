// Write program to count words of size <=4 USING FUNCTION instead of lambda
#include <iostream>
#include <vector>
#include <functional> // for "bind", "placeholders"
#include <sstream>
#include <string>

using namespace std;
using namespace std::placeholders;

string make_plural(size_t ctr, const string& word, const string& ending) {
  return (ctr>1) ? word+ending : word;
}

void print_vector_less_elements(vector<string>& vs, int num_elem_less) {
  for (auto& item : vs) {
    if (item.size() <= num_elem_less)
      cout << item << " ";
  }
  cout << endl;
}

bool check_size(const string& s, string::size_type sz) {
  return s.size() <= sz;
}

int main() {
  // Read from <string> to vector<string> (of words)
  stringstream ss ("the quick red fox jumps over the slow red turtle");
  string word;
  vector<string> words;
  while(ss >> word) {
    words.push_back(word);
  }

  // Count words with <=4 chars
  vector<int>::size_type sz = 4;
  auto cnt = count_if(
    words.begin(), words.end(),
    bind(check_size, _1, sz)
  );

  cout << cnt << " " << make_plural(cnt, "word", "s") << " of length " << sz << " or less\n";
  print_vector_less_elements(words, sz);

  return 0;
}
