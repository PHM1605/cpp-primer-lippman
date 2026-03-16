// Define a <tuple> that holds 3 ints
#include <iostream>

using namespace std;

int main() {
  tuple<int,int,int> tp(10,20,30);
  cout << get<0>(tp) << " " << get<1>(tp) << " " << get<2>(tp) << endl;

  return 0;
}