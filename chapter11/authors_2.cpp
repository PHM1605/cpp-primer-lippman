// Write a program that defines <multimap>  of authors and their work
// Find a specific <author> and his <work>s USING <lower_bound> and <upper_bound>
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
  
  // search
  string search_item("Alain de Botton");
  cout << search_item << ": " << endl;
  for(auto beg=authors.lower_bound(search_item), end=authors.upper_bound(search_item); beg!=end; ++beg) {
    cout << beg->second << endl;
  }

  return 0;
}