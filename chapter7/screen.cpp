// Write Screen class
// g++ screen.cpp 
#include <iostream>
#include <string>
#include <vector>

using namespace std;
 
// Window to control Screen
class Window_mgr {
public:
  using ScreenIndex = vector<Screen>::size_type;
  void clear(ScreenIndex); // this function uses Screen, hence DECLARED-ONLY here, defined later after Screen
  // add a Screen to its collection and return <index>
  ScreenIndex addScreen(const Screen&);

private:
  vector<Screen> screens{ Screen(24,80, ' ')};
};

class Screen {
// friend class to modify Screen from outside
friend void Window_mgr::clear(ScreenIndex); 

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
  // size
  pos Screen::size() const;

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

Screen::pos Screen::size() const {
  return height * width;
}

void Window_mgr::clear(ScreenIndex i) {
  // which Screen we want to clear
  Screen &s = screens[i];
  s.contents = string(s.height*s.width, ' ');
}

Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen& s) {
  screens.push_back(s);
  return screens.size() - 1;
}

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