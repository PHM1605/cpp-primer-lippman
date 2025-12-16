// g++ error_init_list.cpp && ./a.out
#include <iostream>
#include <string>

using namespace std;

// error message without error code
void error_msg(initializer_list<string> il) {
	for (auto beg=il.begin(); beg!=il.end(); beg++) {
		cout << *beg << " ";
	}
	cout << endl;
}

int main (int argc, char *argv[]) {
	
	string expected = "this";
	string actual = "this";

	if (expected != actual) {
		error_msg({"functionX", expected, actual});
	} else {
		error_msg({"functionX", "okay"});
	}

	return 0;
}


