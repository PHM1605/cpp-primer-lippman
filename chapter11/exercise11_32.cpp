// Write a program to print the list of authors and their works ALPHABETICALLY
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print_vector(vector<string>& works) {
  for (auto& work : works) 
    cout << "- " << work << "\n";
}

void print_mmap(multimap<string,string>& mm) {
  auto iter = mm.begin();
  while(iter != mm.end()) {
    const string& author = iter->first;
    auto range = mm.equal_range(author);
    // collect the works from one author
    vector<string> works;
    for (auto one_author_iter=range.first; one_author_iter!=range.second; ++one_author_iter) {
      works.push_back(one_author_iter->second);
    }
    // sort works of one author
    sort(works.begin(), works.end());
    // print that author's works
    cout << author << ": " << endl;
    print_vector(works);

    // done => move to next author
    iter = range.second;
  }
}

int main() {
  multimap<string, string> authors;
  authors.insert({"Alain de Botton", "Titanic"});
  authors.insert({"Alain de Botton", "An apple"});
  authors.insert({"Abcdxyz", "The orange"});
  
  print_mmap(authors);

  return 0;
}