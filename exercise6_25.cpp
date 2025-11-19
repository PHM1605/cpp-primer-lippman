// write a <main> function that takes arguments, concatenate the supplied arguments and print the resulting string
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  cout << "Number of arguments: " << argc-1 << endl;

  string result;
	for (int i=0; i<argc-1; i++){
		result += argv[i];
		if (i!=argc-1)
			result += " "; // add space if not last parameters
	}
	cout << "The entire argument is: " << result << endl;

  return 0;
}