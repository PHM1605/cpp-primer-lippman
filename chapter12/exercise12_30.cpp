// Ask user to type a word; search a document and shows 
// 1. number of occurences
// 2. which lineS and print those lines
// ==> type "elements" to search that word in <exercise12_30_input.txt>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <set>
#include <map>

using namespace std;

class QueryResult;

class TextQuery {
public:
  // Constructors
  TextQuery(ifstream&);
  // process the word "element" to query it in the file
  QueryResult query(const string&) const;

private:
  shared_ptr<vector<string>> file; // lines of an input file
  // map each word to a set of lines
  map<string, shared_ptr<set<size_t>>> wm;  
};

class QueryResult {
public:
private:
  string sought; // "element"...
  shared_ptr<set<size_t>> lines; // ...on which lines?
  shared_ptr<vector<string>> file; // lines of an input file
};

// Constructor of <TextQuery>
TextQuery::TextQuery(ifstream& is): file(new vector<string>) {
  string text;
  while(getline(is, text)) {
    file->push_back(text);
    int n = file->size() - 1; // the current line number

    // read each line; read each word into <map>
    istringstream line(text);
    string word;
    while(line >> word) {
      // lines is an alias to <shared_ptr>
      // - if <word> entry not exist=>created
      // - otherwise get that <shared_ptr> 
      auto& lines = wm[word]; 
      // if we see that word the 1st time
      if (!lines)
        lines.reset(new set<size_t>); // allocate new set
      lines->insert(n); // NOTE: an "insert-to-existed-in-set" does nothing
    }
  }
}

void runQueries(ifstream& infile) {
  // parse the .txt file
  TextQuery tq(infile);
  // interact with user to get word e.g. "element"
  while(true) {
    cout << "enter the word to look for, or q to quit: ";
    string inp_word;
    if (!(cin >> inp_word) || inp_word=="q")
      break;
    print(cout, tq.query(inp_word)) << endl;
  }
}

int main() {
  string input;

  do {
    cout << "Enter a string (empty line to quit): ";
    getline(cin, input);
    if (!input.empty()) {
      cout << "You enter " << input << endl;
    }
  } while(!input.empty());

  return 0;
}