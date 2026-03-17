// Write Quiz program: true/false for 10/100 questions 
// WITH UPDATE BIT function and GRADE function
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

template<size_t N>
size_t grade(const Quiz<N>& q, const bitset<N>& correct) {
  // when answer=0 and result=1 (or vice versa) then it's wrong answer
  // => use XOR ^
  bitset<N> wrong = q.responses ^ correct;
  return N - wrong.count();
}

int main() {
  Quiz<10> answers;

  updateQuiz(answers, 0, true);
  updateQuiz(answers, 1, false);
  updateQuiz(answers, 2, true);
  updateQuiz(answers, 3, true);
  cout << "Student answers: " << answers.responses << endl;
  
  bitset<10> correct(string("1011001010"));
  cout << "Correct answers: " << correct << endl;

  cout << "Score: " << grade(answers, correct) << " / 10" << endl;

  return 0;
}