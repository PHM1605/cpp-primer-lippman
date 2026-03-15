// Define a function template to count the #occur of a given value in <vector>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

template<typename T>
int count_elem(const T& val, const vector<T>& v) {
  int ret = 0;
  for(auto& temp : v) {
    if (temp == val) {
      ret++;
    }
  }
  return ret;
}

// Specialized version to handle "const char*"
template<>
int count_elem<const char*>(const char* const& val, const vector<const char*>& v) {
  int ret = 0;
  for (auto temp: v) {
    if (strcmp(temp, val) == 0) {
      ret ++;
    }
  }
  return ret;
}

int main() {
  vector v1 = {1,2,4,7,2,0};
  cout << "Number of 2: " << count_elem(2, v1) << endl;

  vector<const char*> v2 = {"hi", "hello", "hi", "world"};
  cout << "Number of 'hi': " << count_elem<const char*>("hi", v2) << endl;
  
  return 0;
}