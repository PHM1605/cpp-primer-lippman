// Write a function that check a string is a sub-string from start of another string
#include <iostream>
#include <string>

using namespace std;

bool str_subrange(const string& str1, const string& str2) {
  // same size => return normal equality test
  if (str1.size() == str2.size()) 
    return str1 == str2;
  // find the size of smaller string
  auto size = (str1.size() < str2.size()) ? str1.size() : str2.size();
  // look at each element up to the size of smaller string
  for (decltype(size) i=0; i!=size; i++) {
    if (str1[i] != str2[i])
      return 0;
  }
  return 1;
}

int main() {
  string s1 = "abc";
  string s2 = "ab";
  cout << str_subrange(s1, s2) << endl;
  return 0;
}