#include <iostream>

int main () {
	char ch;
	unsigned vowelCnt = 0;
	unsigned otherCnt = 0;
	while (std::cin >> ch) {
		switch(ch) {
		// any occurence of a, e, i, o, u increments vowelCnt
		case 'a': case 'e': case 'i': case 'o': case 'u':
			++vowelCnt;
			break;
		default:
			++otherCnt;
		}

	}
	std::cout << "Number of vowels: " << vowelCnt << std::endl;
	std::cout << "Number of others: " << otherCnt << std::endl;

	return 0;
}


