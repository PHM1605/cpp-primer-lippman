// Nested <QueryResult> inside <TextQuery>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <set>
#include <map>
#include <string>

using namespace std;

class TextQuery {
public:
  // NEW: nested <QueryResult>
  class QueryResult;

  // Constructors
  TextQuery(ifstream&);
  // process the word "element" to query it in the file
  QueryResult query(const string&) const;

private:
  shared_ptr<vector<string>> file; // lines of an input file
  // map each word to a set of lines
  map<string, shared_ptr<set<size_t>>> wm;
};

// Define nested <QueryResult>
class TextQuery::QueryResult {
  friend ostream& print(ostream&, const QueryResult&);
public:
  // constructor of nested
  QueryResult(string, shared_ptr<set<size_t>>, shared_ptr<vector<string>>);
  // NEW: nested <static> will be visible inside <TextQuery> too
  static int static_mem;
private:
  string sought; // "element"
  shared_ptr<set<size_t>> lines; // ...on which lines?
  shared_ptr<vector<string>> file; // lines of an input file
};

// Define <TextQuery>
TextQuery::TextQuery(ifstream& is): file(new vector<string>) {
  string text;
  while(getline(is, text)) {
    file->push_back(text); // read each line data
    int n = file->size() - 1; // current line number
    // read each line; read each word to <map>
    istringstream line(text);
    string word;
    while(line >> word) {
      auto& lines = wm[word]; 
      // create <set> if not exist
      if (!lines)
        lines.reset(new set<size_t>);
      lines->insert(n);
    }
  }
}

// NEW: define <QueryResult> constructor OUTSIDE TOO
TextQuery::QueryResult::QueryResult(string s, shared_ptr<set<size_t>> p, shared_ptr<vector<string>> f):
  sought(s), lines(p), file(f) {}

int TextQuery::QueryResult::static_mem = 1024;

TextQuery::QueryResult TextQuery::query(const string& sought) const {
  // in case we don't find "sought" => "static": create ONCE every query()-call
  static shared_ptr<set<size_t>> nodata(new set<size_t>);
  // find "element" in "map"
  auto loc = wm.find(sought);
  if (loc == wm.end())
    return QueryResult(sought, nodata, file);
  else
    return QueryResult(sought, loc->second, file);
}

ostream& print(ostream& os, const TextQuery::QueryResult& qr) {
  os << qr.sought << " occurs " << qr.lines->size() << " time(s)" << endl;
  for (auto num: *qr.lines)
    os << " (line " << num+1 << ") " << (*qr.file)[num] << endl;
  return os;
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
  ifstream infile("exercise19_20_input.txt");
  runQueries(infile);

  return 0;
}