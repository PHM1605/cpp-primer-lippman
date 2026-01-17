// Write a program that defines <multimap>  of authors and their work
// Find a specific <author> and his <work>s USING <find> function
#include <map>
#include <iostream>

using namespace std;

// void print_mmap(multimap<string,string>& mm) {
//   for (auto& item: mm) {
//     cout << item.first << ": " << item.second << endl;
//   }
// }

int main() {
  multimap<string, string> authors;
  authors.insert({"Alain de Botton", "Titanic"});
  authors.insert({"Alain de Botton", "An apple"});
  authors.insert({"Abcdxyz", "The orange"});
  
  // find
  string search_item("Alain de Botton");
  auto num_entries = authors.count(search_item);
  auto iter = authors.find(search_item); // 1st entry of that author
  
  cout << "Books of Alain de Botton:\n";
  while(num_entries) {
    cout << iter->second << endl;
    ++iter;
    --num_entries;
  }

  return 0;
}