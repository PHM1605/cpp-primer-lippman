// Write a program to read strings from standard input looking for duplicated words
// return the most-frequent word and its number-of-occurences
// "how now now now brown cow cow" => return "now" and "3"
#include <iostream>
#include <vector>
#include <string>

int main() {
	std::string tmp;
	// storing all strings to vector v
	std::vector<std::string> v;
	while(std::cin >> tmp) {
		v.push_back(tmp);	
	}

	// reading vector v and analyze
	auto beg = v.begin();
	std::string tmpMaxString = *beg;
	int maxOccur = 0;

	while (beg != v.end()) {
		int occur = 0;
		std::string tmpString = *beg;
		while (*beg == tmpString) {
			++occur;
			beg++;
		}
		// the next different word
		if (occur > maxOccur) {
			maxOccur = occur;
			tmpMaxString = tmpString;
		}
	}

	std::cout << "The word " << tmpMaxString << " occurs " << maxOccur << " times\n";
	return 0;
}
