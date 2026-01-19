// Write a function that returns a dynamically allocated vector of ints
// Pass that vector to a function that reads <cin> to give values
// Pass that vector to another function to print values
// NOTE: using <shared_ptr>
#include <memory>
#include <iostream>
#include <vector>

using namespace std;

shared_ptr<vector<int>> alloc_vi() {
  return make_shared<vector<int>>();
}

void read_vector(shared_ptr<vector<int>> v) {
  int x;
  while(cin >> x) {
    v->push_back(x);
  }
}

void print_vector(shared_ptr<vector<int>> v) {
  for(int x: *v) {
    cout << x << " ";
  }
  cout << endl;
}

int main() {
  shared_ptr<vector<int>> v = alloc_vi();
  read_vector(v);
  print_vector(v);

  return 0;
}