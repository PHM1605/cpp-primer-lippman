// write function to generate a "uniformly distributed random"
#include <iostream>
#include <vector>
#include <random>

using namespace std;

vector<unsigned> gen_random_vector(int low_range, int high_range) {
  // NOTE: without "static" the SAME distribution/engine will be called each time
  static uniform_int_distribution<int> u(low_range, high_range); // random range
  static default_random_engine e;

  // NOTE: with seed we will get SAME random runs despite "static"
  // e.seed(123);

  vector<unsigned> ret;
  for(size_t i=0; i<10; i++) {
    ret.push_back(u(e));
  }
  return ret;
}

void print_vec(vector<unsigned>& v) {
  for (auto val: v) {
    cout << val << " ";
  }
  cout << endl;
}

int main() {
  vector<unsigned> random_vector1 = gen_random_vector(0, 20);
  vector<unsigned> random_vector2 = gen_random_vector(0, 20);
  print_vec(random_vector1);
  print_vec(random_vector2);

  return 0;
}