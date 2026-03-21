// Write a word transformation program with RANDOM transformation of each word
// NOTE: we define MULTIPLE DEFINITIONS of each word in the <map> file
#include <iostream>
#include <random>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

// global randomness 
random_device rd;
default_random_engine engine(rd());

// map each word to multiple transforms
map<string, vector<string>> buildMap(ifstream& map_file) {
  map<string, vector<string>> trans_map;
  string key, values;
  while(map_file >> key && getline(map_file, values)) {
    if (values.size() > 1) {
      trans_map[key].push_back(values.substr(1)); // index 0 is leading space => NOT take
    } else {
    throw runtime_error("no rule for " + key);
    }
  }
  return trans_map;
}

// random transform each word (key) with ONE of valueS in <map>
string transform(const string& word, const map<string, vector<string>>& m) {
  auto it = m.find(word);
  if (it != m.end()) {
    const vector<string>& choices = it->second;
    uniform_int_distribution<size_t> dist(0, choices.size()-1);
    return choices[dist(engine)];
  }
  // if no transformation found => return original word
  return word;
}

void word_transform(ifstream& map_file, ifstream& input) {
  auto trans_map = buildMap(map_file);
  // read line by line
  string text;
  while(getline(input, text)) {
    istringstream text_stream(text);
    string word;
    bool first_word = true;
    // read each word in each line
    while(text_stream >> word) {
      // if 1st word => do not print " ", otherwise print " "
      if (!first_word) cout << " ";
      first_word = false;
      // random-transform then print
      cout << transform(word, trans_map);
    }
    cout << endl;
  }
}

int main() {
  ifstream map_file("exercise17_33_map.txt");
  ifstream input("exercise17_33_input.txt");

  word_transform(map_file, input);

  return 0;
}