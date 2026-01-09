// given a vector<int> of even & odd numbers => duplicate odds
#include <iostream>
#include <vector>

using namespace std;

int main () {
  vector<int> vi {1,4,6,7,2,3};
  auto iter = vi.begin();
  while(iter != vi.end()) {
    if ((*iter) % 2) {
      // insert BEFORE location <iter>; return <iter> to added element => HANG
      iter = vi.insert(iter, *iter); 
    }
    ++iter;
  }

  // print debug 
  for (auto& num : vi) {
    cout << num << " ";
  }
  cout << endl;
}