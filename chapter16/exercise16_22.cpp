// Integrate <DebugDelete> (for <shared_ptr>) into <TextQuery>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <memory>
#include <set>

using namespace std;

class DebugDelete {
public:
  DebugDelete(ostream& s=cerr): os(s) {}
  // function calling "delete" on a generic pointer
  template<typename T>
  void operator()(T* p) const { 
    os << "deleting shared_ptr" << endl;
    delete p;
  }

private:
  ostream& os;
};

class QueryResult;
class TextQuery {
public:
  TextQuery(ifstream&);
  // process the word "element" to query it in the file
  QueryResult query(const string&) const;

private:
  shared_ptr<vector<string>> file; // lines of an input file
  map<string, shared_ptr<set<size_t>>> wm; // map each word to a set of lines
};

class QueryResult {
  friend ostream& print(ostream&, const QueryResult&);

public:
  QueryResult(string s, shared_ptr<set<size_t>> p, shared_ptr<vector<string>> f):
    sought(s), lines(p), file(f) {}

private:
  string sought; // "element"
  shared_ptr<set<size_t>> lines; // lines containing the word
  shared_ptr<vector<string>> file; // input file's lines
};

// NOTE: we pass <DebugDelete> here
TextQuery::TextQuery(ifstream& is): file(new vector<string>, DebugDelete()) {
  string text;
  while(getline(is, text)) {
    file->push_back(text);
    int n = file->size() - 1; // the current line number
    // read each line; read each word into <map>
    istringstream line(text);
    string word;
    while(line >> word) {
      // pick a set of line-numbers associated with that <word>
      auto& lines = wm[word];
      if (!lines) 
        // NEW: we will set <deleter> here
        lines = shared_ptr<set<size_t>>(new set<size_t>, DebugDelete());
      lines->insert(n); // NOTE: insert an existed key to a <set> will add NOTHING 
    }
  }
}

// NOTE: we add deleter here
QueryResult TextQuery::query(const string& sought) const {
  // in case we don't find <sought>
  static shared_ptr<set<size_t>> nodata(new set<size_t>, DebugDelete());
  auto loc = wm.find(sought);
  if (loc == wm.find(sought));
  if (loc == wm.end()) 
    return QueryResult(sought, nodata, file);
  else 
    return QueryResult(sought, loc->second, file);
}

ostream& print(ostream& os, const QueryResult& qr) {
  os << qr.sought << " occurs " << qr.lines->size() << " " << (qr.lines->size() > 1 ? "times" : "time") << endl;
  // <num>: which line that word occurs
  for (auto num: *qr.lines) {
    os << "\t(line " << num+1 << ") " << *(qr.file->begin()+num) << endl;
  }
  return os;
}

void runQueries(ifstream& infile) {
  // parse the .txt file
  TextQuery tq(infile);
  // interact with user to get queried word e.g. "element"
  while(true) {
    cout << "enter the word to look for, or q to quit: ";
    string inp_word;
    if (!(cin >> inp_word) || inp_word=="q")
      break;
    print(cout, tq.query(inp_word)) << endl;
  }
}

int main() {
  ifstream infile("exercise16_22_input.txt");
  runQueries(infile);
  
  return 0;
}