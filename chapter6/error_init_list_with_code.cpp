// g++ error_init_list_with_code.cpp && ./a.out
#include <iostream>
#include <string>

using namespace std;

class ErrCode {
public:
  ErrCode(int c): code(c) {}

  string msg() const {
    if (code==0) return "OK";
    return "Error code " + to_string(code);
  }

private:
  int code;
};

// error message with  error code
void error_msg(ErrCode e, initializer_list<string> il) {
	cout << e.msg() << ": ";
	for (const auto& elem: il) {
    cout << elem << " ";
  }
  cout << endl;
}

int main (int argc, char *argv[]) {
	
	string expected = "this";
	string actual = "thit";

	if (expected != actual) {
		error_msg(ErrCode(42), {expected, actual});
	} else {
		error_msg(ErrCode(0), {"functionX", "okay"});
	}

	return 0;
}


