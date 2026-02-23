// Write a class that test if a <string> has length in a range (inclusive) [2,4] and [6,10]
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

void print(const vector<string>& vect, int lower=0, int upper=0) {
  if (!vect.empty()) {
    cout << "Words from range [" << lower << ", " << upper << "]: "; 
    for (auto it = vect.begin(); it!=vect.end(); ++it) {
      cout << *it << " ";
    }
    cout << endl;
  }
}

int main() {
  ifstream ifs("exercise14_38_input.txt");
  string word;
  int lower1 = 2, upper1 = 4; 
  int lower2 = 6, upper2 = 10;
  FilterWords filt_words1(lower1, upper1);
  FilterWords filt_words2(lower2, upper2);

  vector<string> filtered1;
  vector<string> filtered2;
  while(ifs >> word) {
    if (filt_words1(word))
      filtered1.push_back(word);
    else if (filt_words2(word))
      filtered2.push_back(word);
  }

  // display to check
  print(filtered1, lower1, upper1);
  print(filtered2, lower2, upper2);

  return 0;
}