// Capitalize 1st word in string using 'iterator'
#include <iostream>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;

int main() {
    string s("Some string");
    // make sure s is not empty
    for (auto it = s.begin(); it!=s.end() && !isspace(*it); it++) {
        *it = toupper(*it);
    }
    // print 
    cout << s << endl;
    return 0;
}