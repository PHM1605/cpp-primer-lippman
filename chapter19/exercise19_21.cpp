// Write <Token> with <union>
#include <iostream>

using namespace std;

class Token {
public:
  Token(): tok(INT), ival{0} {} // default: union has INT value of 0
  Token(const Token& t): tok(t.tok) { copyUnion(t); } // set flag AND union
  Token& operator=(const Token&);
  // Move constructor
  Token(Token&& t): tok(t.tok) { moveUnion(std::move(t)); }
  // Move assignment
  Token& operator=(Token&&);

  // if <union> has custom class e.g. <string> => must destroy it
  ~Token() {
    if (tok == STR)
      sval.~string();
  }

  // = operators to set different members of <union>
  Token& operator=(const string&);
  Token& operator=(char);
  Token& operator=(int);
  Token& operator=(double);

  // to test
  void print() const {
    switch(tok) {
      case INT: cout << "INT: " << ival << endl; break;
      case CHAR: cout << "CHAR: " << cval << endl; break;
      case DBL: cout << "DBL: " << dval << endl; break;
      case STR: cout << "STR: " << sval << endl; break;
    }
  }

// Token must have BOTH <discriminant> (keep track of union's state) and <union>
private:
  enum {INT, CHAR, DBL, STR} tok; // tok: variable of type "unnamed enum" that can have 1 of 4 values;
  union {
    char cval;
    int ival;
    double dval;
    string sval;
  };

  // check discriminant to copy <union>'s member
  void copyUnion(const Token&);
  void moveUnion(Token&&);
};

Token& Token::operator=(int i) {
  // NOTE: ALWAYS call <string>'s destructor if current token is holding a <string>
  if (tok==STR)
    sval.~string();
  ival = i;
  tok = INT;
  return *this;
}

Token& Token::operator=(double d) {
  if (tok==STR)
    sval.~string();
  dval = d;
  tok = DBL;
  return *this;
}

Token& Token::operator=(char c) {
  if (tok==STR)
    sval.~string();
  cval = c;
  tok = CHAR;
  return *this;
}

Token& Token::operator=(const string& s) {
  // if we already hold a <string> => reassigning only
  if (tok==STR)
    sval = s;
  else 
    // NEW: "placement new" to put that member TO AN ADDRESS
    new (&sval) string(s);
  tok = STR;
  return *this;
}

// NOTE: we are SURE that current object is NOT holding a <string>. Reason:
// - in default constructor: <union> default initialized to 1st member of <INT>
// - in operator=: check the "if" condition
void Token::copyUnion(const Token& t) {
  switch(t.tok) {
    case Token::INT: ival=t.ival; break;
    case Token::CHAR: cval=t.cval; break;
    case Token::DBL: dval=t.dval; break;
    // to copy a <string> to a non-<string> => use "placement new"
    case Token::STR: new(&sval) string(t.sval); break;
  }
}

void Token::moveUnion(Token&& t) {
  switch(t.tok) {
    case INT: ival = t.ival; break;
    case CHAR: cval = t.cval; break;
    case DBL: dval = t.dval; break;
    case STR: new(&sval) string(std::move(t.sval)); break; 
  }
}

Token& Token::operator=(const Token& t) {
  // if this object holds a <string> but coming object doesn't => free old string
  if (tok==STR && t.tok!=STR)
    sval.~string();
  // if this object holds a <string> AND coming object does too
  if (tok==STR && t.tok==STR)
    sval = t.sval;
  // if this object does NOT hold a string
  else 
    copyUnion(t);
  tok = t.tok;
  return *this;
}

// Move assignment
Token& Token::operator=(Token&& t) {
  // if this object holds a <string> but coming object doesn't => free old string
  if (tok==STR && t.tok!=STR)
    sval.~string();
  // if this object holds a <string> AND coming object does too
  if (tok==STR && t.tok==STR)
    sval = std::move(t.sval);
  // if this object does NOT hold a string
  else
    moveUnion(std::move(t));
  tok = t.tok;
  return *this;
}

int main() {
  // assignment
  Token t1;
  t1 = 42;
  t1.print();

  Token t2;
  t2 = string("hello");
  t2.print();

  // copy constructor
  Token t3 = t2;
  t3.print();

  // move constructor
  Token t4 = std::move(t2);
  t4.print();

  // move assignment
  Token t5;
  t5 = std::move(t4);
  t5.print();

  return 0;
}