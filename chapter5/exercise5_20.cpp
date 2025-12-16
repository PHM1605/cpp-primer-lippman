// Write a program to read a sequence of strings from stdin; until either same words occur twice of all words have been read
#include <iostream>
#include <string>

int main() {
  std::string buf;
  std::string prev;
  bool res = false;
  while (std::cin >> buf) {
    if (!prev.empty() && prev==buf) {
      res = true;
      break;
    }
    prev = buf;
  }
  if (res)
    std::cout << "The word " + prev + " occurs twice in succession" << std::endl;
  else 
    std::cout << "No two words are repeated\n";
}