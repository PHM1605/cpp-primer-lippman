// make a "float-random-generator"
#include <iostream>
#include <random>

using namespace std;

int main() {
  default_random_engine e;
  uniform_real_distribution<double> u(0,1); // or uniform_real_distribution<> u(0,1) to use default; it's still "double" anyway
  for (size_t i=0; i<10; i++) {
    cout << u(e) << " ";
  }
  cout << endl;

  return 0;
}