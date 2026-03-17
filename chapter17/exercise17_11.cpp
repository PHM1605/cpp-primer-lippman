// Write Quiz program: true/false for 10/100 questions
#include <iostream>
#include <bitset>

using namespace std;

template<size_t T>
struct Quiz {
  bitset<T> responses;
};

int main() {
  Quiz<10> q;
  q.responses.set(0); // set 1 to question 0
  q.responses.set(3); // set 1 to question 3
  q.responses.reset(3); // set 0 to question 3
  
  cout << q.responses << endl;

  return 0;
}