#include <iostream>
#include <string>

using namespace std;

int main (int argc, char *argv[]) {
	
	cout << argc << endl;

	string result;
	for (int i=0; i<argc; i++){
		result += argv[i];
		if (i!=argc-1)
			result += " "; // add space if not last parameters
	}
	cout << "The entire argument is: " << result << endl;

	return 0;
}


