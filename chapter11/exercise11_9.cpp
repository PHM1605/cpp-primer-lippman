// Define a <map> that associates {word: list<int> of line numbers that word occurs}
#include <map>
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
  map<string, list<int>> word_occur;
  
  ifstream infile("exercise11_9_input.txt");
  string line;
  int line_no = 0;
  // read each line in file
  while(getline(infile, line)) {
    ++line_no;
    // read each word in each line
    string word;
    istringstream iss(line);
    while(iss >> word) {
      word_occur[word].push_back(line_no);
    }
  }

  // print result
  for (auto& pr: word_occur) {
    cout << pr.first << " occurs on line(s): ";
    for (int i : pr.second) 
      cout << i << " ";
    cout << endl;
  }

  return 0;
}