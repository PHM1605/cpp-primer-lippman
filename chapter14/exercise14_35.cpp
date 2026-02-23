// Write <PrintString> and <ReadString> that write to stdout/ read from stdin
#include <iostream>
#include <sstream>

using namespace std;

class PrintString {
public:
  PrintString(ostream& o = cout, char c = ' '):
    os(o), sep(c) {}

  void operator()(const string& s) const {
    os << s << sep << endl;
  }
private:
  ostream& os;
  char sep;
};

class ReadString {
public:
  ReadString(istream& i = cin):
    is(i) {}

  string operator()() {
    string line;
    if (getline(is, line))
      return line;
    else
      return string();
  }

private:
  istream& is;
};

int main() {
  string s = "A random string";
  cout << "\n=== Test PrintString ===\n";
  // print to stdout
  PrintString printer;
  printer(s);
  // print to stderr
  PrintString errors(cerr, 'x');
  errors(s);
  // to use with generic algorithm
  // foreach(vs.begin(), vs.end(), PrintString(cerr, 'x'));

  cout << "\n=== Test ReadString ===\n";
  istringstream iss("first line\nsecond line\n");
  ReadString reader(iss);

  cout << reader() << endl;
  cout << reader() << endl;
  cout << reader() << endl;

  return 0;
}