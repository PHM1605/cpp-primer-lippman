// Write Screen class
// g++ screen.cpp 
#include <iostream>
#include <string>
#include <vector>

using namespace std;
 
class Screen {
public:
  typedef string::size_type pos;
  // using pos = string::size_type;

  // constructor
  Screen() = default;
  Screen(pos ht, pos wd): height(ht), width(wd), contents(ht*wd, 'x') {} // exercise7_24; we use 'x' instead of ' ' to see
  Screen(pos ht, pos wd, char c): height(ht), width(wd), contents(ht*wd, c) {} 

  // functions
  // character at cursor position
  char get() const {
    return contents[cursor];
  }
  char get(pos r, pos c) const; 
  // move <cursor> to a location
  Screen& move(pos r, pos c);
  // set pixel at certain location
  Screen& set(char);
  Screen& set(pos, pos, char);
  // display. NOTE: 
  // - const object => call const function; but CANNOT call normal function => we must return CONST SCREEN
  // - normal object => call whatever is ok  => choose NON-CONST SCREEN to return
  Screen& display(ostream &os) {
    do_display(os);
    return *this; // normal Screen object
  }
  const Screen& display(ostream& os) const {
    do_display(os);
    return *this; // const Screen object
  }

private:
  pos cursor = 0; // 1 number accessing whole screen; IN-CLASS INITIALIZER for <cursor>
  pos height = 0, width = 0;
  string contents; // string of <area> number of chars

  void do_display(ostream& os) const {
    os << contents << endl;
  }
};

inline char Screen::get(pos r, pos c) const {
  pos row = r*width;
  return contents[row+c];
}

inline Screen& Screen::move(pos r, pos c) {
  pos row = r*width;
  cursor = row+c;
  return *this;
}

inline Screen& Screen::set(char c) {
  contents[cursor] = c;
  return *this;
}

inline Screen& Screen::set(pos r, pos col, char ch) {
  contents[r*width+col] = ch;
  return *this;
}

class Window_mgr {
private:
  vector<Screen> screens{ Screen(24,80, ' ')};
};

int main() {
  Screen myscreen = Screen(800, 600, 'x');

  // Overloading member functions testing
  myscreen = myscreen.move(100, 200);
  char ch = myscreen.get(); // get <char> at <cursor> location (100,200)
  cout << "Character at first get: " << ch << endl; 
  ch = myscreen.get(10, 20); // get <char> at <cursor> location (10,20)
  cout << "Character at second get: " << ch << endl; 

  // Set a pixel value testing
  myscreen.move(10,20).set('#');
  ch = myscreen.get(10, 20);
  cout << "Character at 3rd get: " << ch << endl; 

  // Screen display
  // non-const Screen version
  Screen myScreen(5, 3, 'x');
  myScreen.move(4,0).set('#').display(cout);
  cout << "\n";
  // const Screen version
  const Screen blank(5, 3);
  blank.display(cout);

  return 0;
}