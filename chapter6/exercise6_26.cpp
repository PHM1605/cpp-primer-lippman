// write a <main> that prints arguments passed to <main>
// => test ./a hello world
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  cout << "Number of arguments: " << argc-1 << endl;
  cout << "The argument list is: ";
	for (int i=1; i<argc; i++){
    cout << argv[i];
    cout << " ";
	}
	cout << endl;

  return 0;
}