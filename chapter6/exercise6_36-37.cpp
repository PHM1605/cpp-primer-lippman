#include <string>

using namespace std;

// Exercise 6.36: Write the declaration for a function that returns a reference to an array of 10 strings
string (&function1(void))[10];

// Exercise 6.37: Write the declaration for a function that returns a reference to an array of 10 strings
// 1/ using type alias
typedef string (&arrString)[10];
arrString function2();
// 2/ using trailing return
auto function3() -> string (&)[10];
// 3/ using <decltype>
string arrString2[10]; // array of 10 strings
decltype(arrString2) &function4();

