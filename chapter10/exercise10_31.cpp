// Use <stream_iterator>, <sort>, <unique_copy>
// to read sequence of ints from <cin>, sort, and UNIQUE-WRITE to <cout>
// Test: 1 4 4 78 23 5 23 40
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  // read <cin> to vector<int>
  istream_iterator<int> is_iter(cin);
  istream_iterator<int> eof;
  vector<int> vi (is_iter, eof);

  // sort
  sort(vi.begin(), vi.end());

  // print to <cout>
  ostream_iterator<int> os_iter(cout, " ");
  unique_copy(vi.begin(), vi.end(), os_iter);

  return 0;
}