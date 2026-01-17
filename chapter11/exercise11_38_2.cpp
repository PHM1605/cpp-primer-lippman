// Implement the word-transformation program
// Convert abbr.text in <exercise11_33_input.txt> using a dictionary in <exercise11_33_map.txt>
// USING <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

// read the dictionary raw text => convert to real DICT
unordered_map<string, string> buildMap(ifstream& map_file) {
  unordered_map<string,string> trans_map;
  string key, value;
  // "my_key this is value" => "my_key" & " this is value" (NOTE: the starting ' ')
  while(map_file >> key && getline(map_file, value)) {
    if (value.size() > 1)
      trans_map[key] = value.substr(1); // remove starting ' '
    else 
      throw runtime_error("no rule for " + key);
  }
  return trans_map;
}

//take a <word> and return transformation if there is one
const string& transform(const string& word, const unordered_map<string,string>& m) {
  auto map_it = m.find(word);
  // if word is in <map> => return its transform
  if (map_it != m.cend())
    return map_it->second;
  // ... else return original
  else 
    return word;
}

void word_transform(ifstream& map_file, ifstream& input) {
  auto trans_map = buildMap(map_file);
  string text;
  // read each line into <string>
  while(getline(input, text)) {
    istringstream stream(text);
    string word;
    bool firstword = true; // flag 1st word (we print only that word) or not (we print a " " char additionally)
    while(stream >> word) {
      if (firstword)
        firstword = false;
      else
        cout << " "; // print a space between word if not the 1st word
      cout << transform(word, trans_map);
    }
    cout << endl;
  }
}

int main() {
  ifstream map_file("exercise11_33_map.txt");
  ifstream input("exercise11_33_input.txt");
  
  word_transform(map_file, input);

  return 0;
}