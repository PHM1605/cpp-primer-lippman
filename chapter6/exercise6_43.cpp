// Rewrite the <isShorter> function from $6.2.2 to be <inline>
#include <iostream>
#include <string>

using namespace std;

inline bool isShorter(const string& s1, const string& s2) {
  return s1.size() < s2.size();
}

int main() {
  cout << "Is \'abc\' shorter than \'abcd\': " << isShorter("abc", "abcd") << endl;
  
  return 0;
}