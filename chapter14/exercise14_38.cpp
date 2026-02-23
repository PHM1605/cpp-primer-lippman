// Write a class that test if a <string> has length in a range (inclusive) [5,10]
// Use that to write a program that reports how many words in a text file within that bound
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class FilterWords {
public:
  FilterWords(const int& lower, const int& upper):
    lower_bound(lower), upper_bound(upper) {}
  bool operator()(const string& s) {
    return s.size()>=lower_bound && s.size()<=upper_bound;
  }
private:
  int lower_bound;
  int upper_bound;
};

int main() {
  ifstream ifs("exercise14_38_input.txt");
  string word;
  int lower = 5; 
  int upper = 10;
  FilterWords filt_words(lower, upper);

  vector<string> filtered;
  while(ifs >> word) {
    if (filt_words(word))
      filtered.push_back(word);
  }

  // display to check
  cout << "Words from range [" << lower << ", " << upper << "]: "; 
  for (auto it = filtered.begin(); it!=filtered.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;

  return 0;
}