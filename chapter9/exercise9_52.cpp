// Use a <stack> to process parenthesized expressions => check if "(a+(b*c))" or "(a+b))" is valid or not (True for 1st, False for 2nd)
#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool check_valid(const string& expr) {
  stack<char> st;
  for (char c: expr) {
    if (c=='(') {
      st.push(c);
    } else if (c==')') {
      if (st.empty())
        return false;
      st.pop(); // remove the '('
    }
  }
  return st.empty();
}

int main() {
  cout << check_valid("(a+(b*c))") << endl;
  cout << check_valid("(a+b))") << endl;
  return 0;
}