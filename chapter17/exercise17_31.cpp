// Create a "random-game" program
#include <iostream>
#include <random>

using namespace std;

bool play(bool is_computer_first) {
  if (is_computer_first)
    return true; // indicate user lost
  else 
    return false; // indicate user wins
}

int main() {
  string resp; // response
  random_device rd;
  default_random_engine e(rd());
  bernoulli_distribution b(0.55);

  do {
    bool first = b(e); // which one goes first (player or computer)
    cout << (first ? "We go first" : "You get go first") << endl;
    // play the game; passing flag who goes first(true=computer; false=user)
    cout << (play(first) ? "sorry, you lost" : "congrats, you won") << endl;
    cout << "play again? Enter 'yes' or 'no' " << endl;
  } while(cin >> resp && resp[0]=='y');

  return 0;
}