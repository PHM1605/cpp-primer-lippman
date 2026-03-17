// Write Quiz program: true/false for 10/100 questions WITH UPDATE BIT function
#include <iostream>
#include <bitset>

using namespace std;

template<size_t N>
struct Quiz {
  bitset<N> responses;
};

template<size_t N>
void updateQuiz(Quiz<N>& q, size_t question, bool value) {
  q.responses.set(question, value);
}

int main() {
  Quiz<10> q;
  updateQuiz(q, 0, true);
  updateQuiz(q, 3, true);
  updateQuiz(q, 3, false);
  
  cout << q.responses << endl;

  return 0;
}