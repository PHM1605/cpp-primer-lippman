// classify high-pass, pass, fail grades, adding also 'low-pass' for grades between 60 and 75 exclusive 
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

int main() {
    int grade=65;
    string final_grade;
    final_grade = (grade>=90) ? "high-pass"
        : (grade>=75) ? "pass"
            : (grade>=60) ? "low-pass"
                : "fail";
    cout << final_grade << endl;
    return 0;
}