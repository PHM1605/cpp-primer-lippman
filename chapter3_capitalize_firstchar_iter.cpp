// Capitalize 1st character in string using 'iterator'
#include <iostream>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;

int main() {
    string s("some string");
    // make sure s is not empty
    if (s.begin() != s.end()) {
        auto it = s.begin();
        *it = toupper(*it);
    }
    // print 
    cout << s << endl;
    return 0;
}