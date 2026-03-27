// Modify <Screen> class to check "pointer to member"
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

  // static function to get "pointer-to-member"
  static const string Screen::* data() {
    return &Screen::contents;
  }
  static const size_t Screen::* cursor_pointer() {
    return &Screen::cursor;
  }

private:
  string contents;
  size_t cursor;
  size_t height, width;
};

Screen& Screen::move(size_t r, size_t c) {
  size_t row = r*width;
  cursor = row + c;
  return *this;
}
Screen& Screen::set(char c) {
  contents[cursor] = c;
  return *this;
}

int main() {
  // // pointer to a "const string member"; we can "read" info but cannot "write"
  const string Screen::* pdata = Screen::data();

  // Use "pointer to member" => we must BOUND <pdata> to an object <myScreen>
  Screen myScreen = Screen(16, 16, 'x');
  myScreen.move(10, 5).set('#');
  Screen *pScreen = &myScreen;

  // *pdata => we get the member
  // then <object>. or <object>->
  auto s = myScreen.*pdata;
  // s = pScreen->*pdata;

  // Use "pointer to member" for "cursor"
  const size_t Screen::* p_cursor = Screen::cursor_pointer();
  auto my_cursor = myScreen.*p_cursor;
  //my_cursor = pScreen->*p_cursor;

  // some display to check

  cout << "Screen content: " << s << endl;
  cout << "Cursor loc: " << my_cursor << endl;

  return 0;
}