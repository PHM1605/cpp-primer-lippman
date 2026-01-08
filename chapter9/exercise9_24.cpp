// Write a program that fetches the 1st element of a <vector> using <at>, subscript, <front> and <begin>
// Test with an empty vector
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> vi {1,6,2,4};
  cout << vi.at(0) << endl;
  cout << vi[0] << endl;
  cout << vi.front() << endl;
  cout << *vi.begin() << endl;

  // test with empty vector
  vector<int> v_empty;
  cout << v_empty.at(0) << endl;
  cout << v_empty[0] << endl;
  cout << v_empty.front() << endl;
  cout << *v_empty.begin() << endl;

  return 0;
}