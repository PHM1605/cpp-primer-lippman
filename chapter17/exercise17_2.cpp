// Define a <tuple> that holds a <string>, a vector<string> and a pair<string,int>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  tuple<string,vector<string>,pair<string,int>> tp(
    string("hello"),
    vector<string>{"hi", "world"}, 
    pair<string,int> {"a",1}
  );
  cout << "1st element: " << get<0>(tp) << endl; 
  cout << "2nd element:\n";
  for (auto v: get<1>(tp)) {
    cout << v << endl;
  }
  cout << "3rd element:\n";
  cout << get<2>(tp).first << " " << get<2>(tp).second << endl;

  return 0;
}