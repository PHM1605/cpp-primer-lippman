// Write generic <compare> function
#include <iostream>
#include <cstring>

using namespace std;

template <typename T>
int compare(const T& v1, const T& v2) {
  if (v1 < v2) return -1;
  if (v1 > v2) return 1;
  return 0; 
}

template<unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M]) {
  auto ret = strcmp(p1, p2);
  if (ret < 0) return -1;
  if (ret > 0) return 1;
  return 0;
}

int main() {
  cout << "Is 2 greater than 1? " << compare(2,1) << endl;
  cout << "Is 'hi' smaller than 'mom'? " << compare("hi", "mom") << endl;
  return 0;
}