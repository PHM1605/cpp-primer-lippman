// Write generic "Screen" class
#include <iostream>
#include <sstream>

using namespace std;

// forward declaration for "friend"
template<size_t H, size_t W> class Screen;
template<size_t H, size_t W> ostream& operator<<(ostream&, const Screen<H,W>&);
template<size_t H, size_t W> istream& operator>>(istream&, Screen<H,W>&);

template<size_t H, size_t W>
class Screen {
  // NOTE: <> we tell the compiler that "operator<<" and "operator>>" are template AS ABOVE 
  friend ostream& operator<< <>(ostream&, const Screen<H,W>&);
  friend istream& operator>> <>(istream&, Screen<H,W>&);
public:
  Screen(): contents(H*W, ' ') {}
private:
  string contents;
};

// output operator
template<size_t H, size_t W>
ostream& operator<<(ostream& os, const Screen<H,W>& s) {
  for (size_t r=0; r<H; r++){
    for (size_t c=0; c<W; c++) {
      os << s.contents[r*W+c];
    }
    os << endl;
  }
  return os;
}
// input operator
template<size_t H, size_t W>
istream& operator>>(istream& is, Screen<H,W>& s) {
  // read <stdin> into <tmp> string
  string tmp;
  getline(is, tmp);
  // read "just-enough" to fill H*W screen
  s.contents = tmp.substr(0, H*W);
  return is;
}

int main() {
  stringstream ss {"this is a test string. Try to make it longer than 36 chars. Is that now long enough? Try to add some more words"};
  Screen<6,6> s;
  // Read <stringstream>
  ss >> s;
  // Print <stringstream>
  cout << "\nScreen:\n";
  cout << s;

  return 0;
}