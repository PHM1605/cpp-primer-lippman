// Use function objects, write a function to 
// "find 1st string that's not equal to 'pooh' "
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional> // for <bind> 

using namespace std;

int main() {
  vector<string> words = {"pooh", "pooh", "tiger", "piglet"};

  auto it = find_if(
    words.begin(), 
    words.end(),
    bind(not_equal_to<string>(), placeholders::_1, "pooh")
  );
  if (it!=words.end())
    cout << "First not equal to 'pooh': " << *it << endl;
  else
    cout << "All are pooh" << endl;
    
  return 0;
}