// Write a program that defines <multimap>  of authors and their work
// Using <count> and <find> to search
#include <map>
#include <iostream>

using namespace std;

void print_mmap(multimap<string,string>& mm) {
  for (auto& item: mm) {
    cout << item.first << ": " << item.second << endl;
  }
}

int main() {
  multimap<string, string> authors;
  authors.insert({"Alain de Botton", "Titanic"});
  authors.insert({"Alain de Botton", "An apple"});
  authors.insert({"Abcdxyz", "The orange"});
  
  // find
  string search_item("Alain de Botton");
  auto num_entries = authors.count(search_item);
  auto iter = authors.find(search_item); // 1st entry of that author
  // what if not exists
  if (iter == authors.end()) {
    cout << "Don't find Alain de Botton" << endl;
    return 1;
  }
  cout << "Books of Alain de Botton:\n";
  while(num_entries) {
    cout << iter->second << endl;
    ++iter;
    --num_entries;
  }

  // erase that author  
  auto num_books = authors.erase("Alain de Botton");
  cout << "\nList of authors\n";
  print_mmap(authors);

  return 0;
}