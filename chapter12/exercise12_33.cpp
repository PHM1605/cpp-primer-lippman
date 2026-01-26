// Ask user to type a word; search a document and shows 
// 1. number of occurences
// 2. which lineS and print those lines
// ==> type "elements" to search that word in <exercise12_30_input.txt>
// NOTE: add to <QueryResult> the <begin()> and <end()> that return <set-iterator>s of <lines>
// ... add <add_file()> that returns a <shared_ptr> to the file in <QueryResult>
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
friend ostream& print(ostream&, const QueryResult&);
public:
  // Constructor
  QueryResult(string s, shared_ptr<set<size_t>> p, shared_ptr<vector<string>> f):
    sought(s), lines(p), file(f) {}

  set<size_t>::iterator begin();
  set<size_t>::iterator end();
  shared_ptr<vector<string>> get_file();

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

ostream& print(ostream& os, const QueryResult& qr) {
  os << qr.sought << " occurs " << qr.lines->size() << " " << (qr.lines->size() > 1 ? "times": "time") << endl;
  // <num>: which line that word occurs
  for (auto num: *qr.lines)
    os << "\t(line " << num+1 << ") " << *(qr.file->begin()+num) << endl;
  return os;
}

QueryResult TextQuery::query(const string& sought) const {
  // In case we don't find <sought>
  static shared_ptr<set<size_t>> nodata(new set<size_t>);
  // try to find <sought> in <map>
  auto loc = wm.find(sought);
  if (loc == wm.end())
    return QueryResult(sought, nodata, file);
  else 
    return QueryResult(sought, loc->second, file);
}

void runQueries(ifstream& infile) {
  // parse the .txt file
  TextQuery tq(infile);
  
  // prove <begin()>, <end()> and <get_file()> by finding the word "is"
  QueryResult result = tq.query(string("is"));
  for (auto it = result.begin(); it != result.end(); ++it) {
    cout << "found on line " << (*it+1) << endl;
  }

  auto f = result.get_file();
  cout << "line 1 content: " << (*f)[0] << endl;
}

// QueryResult operations
set<size_t>::iterator QueryResult::begin() {
  return lines->begin();
}

set<size_t>::iterator QueryResult::end() {
  return lines->end();
}

shared_ptr<vector<string>> QueryResult::get_file() {
  return file;
}

int main() {
  ifstream infile("exercise12_30_input.txt");
  runQueries(infile);

  return 0;
}