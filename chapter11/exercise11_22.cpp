// Word counting program using <insert> instead of subscripting
// typing: "this is a test file to test word count what is this"
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int main() {
  map<string,size_t> word_count;
  string word;
  while(cin >> word) {
    auto result = word_count.insert({word, 1});
    // 2nd element of <result> shows if that word is inserted to <map>
    // 1st element shows <iterator> to that element
    if (!result.second) {
      ++(result.first->second);
    }
  }

  // print 
  for(const auto& p: word_count) {
    cout << p.first << " occurs " << p.second << " times" << endl;
  }

  return 0;
}