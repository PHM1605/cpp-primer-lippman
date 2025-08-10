// Give two vectors of ints, write a program to determine whether one vector is a prefix of the other
// v1 {0, 1, 1, 2}; v2 {0, 1, 1, 2, 3, 5, 8} => return True
#include <vector>
#include <iostream>

bool is_prefix(std::vector<int> v1, std::vector<int> v2) {
  int i;
  for (i=0; i < v1.size() && i < v2.size(); i++) {
    if (v1[i] != v2[i]) break;
  }
  if (i==v1.size() || i==v2.size()) {
    return true;
  }
  return false;
}

int main() {
  std::vector<int> v1 {0, 1, 1, 2};
  std::vector<int> v2 {0, 1, 1, 2, 3, 5, 8};

  std::cout << "Is v1 substring of v2 or vice versa? " << is_prefix(v2, v1) << std::endl;
  return 0;
}