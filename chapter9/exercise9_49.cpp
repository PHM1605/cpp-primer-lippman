// A letter has ascender if it's too tall i.e. "bdhklt"
// A letter has descender if it's too deep i.e. "fgjpqy"
// Write a program that reads a file containing words and reports the longest word that has neither ascenders or descenders
#include <iostream>
#include <fstream>

using namespace std;

int main() {
  string ascender = "bdhklt";
  string descender = "fgjpqy";
  string forbidden = ascender + descender;
  fstream fs("exercise9_49.txt");

  string word;
  string longest;
  while(fs >> word) {
    if (word.find_first_of(forbidden) == string::npos) {
      if (word.size() > longest.size())
        longest = word;
    }
  }

  cout << "Longest word without ascenders/descenders: " << longest << endl;

  return 0;
}