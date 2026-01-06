// show example of each of 6 ways to create and initialize a <vector>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <forward_list>
#include <deque>
#include <array>

using namespace std;

int main() {
  list<string> authors = {"Milton", "Shakespeare", "Austen"};
  vector<const char*> articles = {"a", "an", "the"};
  // way 1: matching containers  
  list<string> list2(authors);
  // way 2: no need of matching; but we must PASS ITERATORS
  forward_list<string> words(articles.begin(), articles.end());
  // way 3: only a part of a big container
  auto it = authors.begin();
  advance(it, 2); // because list<> doesn't support begin()+2, so we use advance() function of list<>
  deque<string> authList(authors.begin(), it);
  // way 4: give <size> and <init-value>
  vector<int> ivec(10, -1); 
  list<string> svec(10, "hi!");
  // way 5: give <size> only; so initialized value is default (NOTE: only for type with DEFAULT CONSTRUCTOR)
  forward_list<int> ivec2(10);
  // way 6: <array> must have SIZE 
  array<int,10> ia1 = {0,1,2,3}; // the rest of elements are 0
  array<int,10> copy = ia1; // copy CPP arrays possible

  return 0;
}