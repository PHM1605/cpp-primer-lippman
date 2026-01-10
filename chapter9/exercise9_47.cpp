// Write a program that finds occurences of characters and numerics in the string <s>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string digits = "0123456789";
const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

// using <find_first_of>
void find_occurences_1(string& s, vector<string::size_type>& num_occur, vector<string::size_type>& alpha_occur) {
  // find numbers
  string::size_type pos = 0;
  while( (pos = s.find_first_of(digits, pos)) != string::npos) {
    num_occur.push_back(pos);
    ++pos;
  }
  // find alphas
  pos = 0;
  while( (pos = s.find_first_of(letters, pos)) != string::npos) {
    alpha_occur.push_back(pos);
    ++pos;
  }
}

// using <find_first_not_of>
void find_occurences_2(string& s, vector<string::size_type>& num_occur, vector<string::size_type>& alpha_occur) {
  // find numbers
  string::size_type pos = 0;
  while( (pos = s.find_first_not_of(letters, pos)) != string::npos) {
    if (digits.find(s[pos]) != string::npos)
      num_occur.push_back(pos);
    ++pos;
  }

  // find alphas
  pos = 0;
  while( (pos = s.find_first_not_of(digits, pos)) != string::npos) {
    if (letters.find(s[pos]) != string::npos)
      alpha_occur.push_back(pos);
    ++pos;
  }
}

int main() {
  string s = "ab2c3d7R4E6";
  vector<string::size_type> num_occur;
  vector<string::size_type> alpha_occur;

  // test 1st way 
  find_occurences_1(s, num_occur, alpha_occur);
  cout << "Places of numbers: ";
  for (auto num: num_occur) {
    cout << num << " ";
  }
  cout << endl;
  cout << "Places of alphas: ";
  for (auto alpha: alpha_occur) {
    cout << alpha << " ";
  }
  cout << endl;

  // test 2nd way
  num_occur.clear();
  alpha_occur.clear();
  find_occurences_2(s, num_occur, alpha_occur);
  cout << "Places of numbers: ";
  for (auto num: num_occur) {
    cout << num << " ";
  }
  cout << endl;
  cout << "Places of alphas: ";
  for (auto alpha: alpha_occur) {
    cout << alpha << " ";
  }
  cout << endl;

  return 0;
}