// Modify <Screen> class to use "pointer-to-member-function" to move cursor
#include <iostream>

using namespace std;

class Screen {
public:
  Screen() = default;
  Screen(size_t ht, size_t wd): 
    cursor(0), height(ht), width(wd), contents(ht*wd, 'x') {} 
  Screen(size_t ht, size_t wd, char c):
    cursor(0), height(ht), width(wd), contents(ht*wd, c) {}

  char get_cursor() const { 
    return contents[cursor]; 
  }
  char get(size_t r, size_t c) const {
    size_t row = r*width;
    return contents[row+c];
  }
  // move <cursor> to a location
  Screen& move(size_t r, size_t c);
  // set cursor location to a value
  Screen& set(char c);
  
  // display content on screen; '_' at cursor location
  void display();

  // NEW: functions to move cursor in a direction WITH "pointer-to-member-function"
  // NOTE: we don't use directly; we use "move"
private:
  Screen& home() {
    cursor = 0;
    return *this;
  }
  Screen& forward() {
    if (cursor+1 < contents.size()) ++cursor;
    return *this;
  }
  Screen& back() {
    if (cursor>0) --cursor;
    return *this;
  }
  Screen& up() {
    if (cursor >= width) cursor -= width;
    return *this;
  }
  Screen& down() {
    if (cursor+width < contents.size()) cursor += width;
    return *this;
  } 
  // type: pointer to member function WITH zero arguments, return <Screen&>
  using Action = Screen& (Screen::*)();
  // Array of many Actions (many pointers) 
  static Action Menu[];
public:
  // NEW: here is our main <move> function
  enum Directions {HOME, FORWARD, BACK, UP, DOWN};
  Screen& move(Directions);

private:
  string contents;
  size_t cursor;
  size_t height, width;
};

// NEW: Setup menu of Actions
Screen::Action Screen::Menu[] = {
  &Screen::home,
  &Screen::forward,
  &Screen::back,
  &Screen::up,
  &Screen::down
};

Screen& Screen::move(Directions cm) {
  return (this->*Menu[cm])(); // activate corresponding "pointer-to-member-function"
}

Screen& Screen::move(size_t r, size_t c) {
  size_t row = r*width;
  cursor = row + c;
  return *this;
}
Screen& Screen::set(char c) {
  contents[cursor] = c;
  return *this;
}

void Screen::display() {
  for (size_t r=0; r<height; ++r) {
    for(size_t c=0; c<width; ++c) {
      size_t idx = r*width+c;
      if (idx == cursor) cout << '_';
      else cout << contents[idx];
    }
    cout << endl;
  }
}

int main() {
  // Use "pointer to member" => we must BOUND <pdata> to an object <myScreen>
  Screen myScreen = Screen(8, 16, 'x');
  myScreen.move(3, 5).set('#').move(2,1);
  cout << "-----------------------------------------\n";
  myScreen.display();
  cout << "-----------------------------------------\n";
  // Test "pointer-to-member-function"
  myScreen.move(Screen::HOME);
  myScreen.display();
  cout << "-----------------------------------------\n";
  myScreen.move(Screen::DOWN);
  myScreen.display();
  cout << "-----------------------------------------\n";

  return 0;
}