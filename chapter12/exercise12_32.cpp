// Ask user to type a word; search a document and shows 
// 1. number of occurences
// 2. which lineS and print those lines
// ==> type "elements" to search that word in <exercise12_30_input.txt>
// NOTE: USE <StrBlob> instead of vector<string> (exercise12_2)
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <set>
#include <map>
#include <vector>

using namespace std;

// <StrBlob> definition
class StrBlob {
public:
  StrBlob();
  StrBlob(initializer_list<string> il);

  string& operator[](size_t i);
  const string& operator[] (size_t i) const;

  size_t size() const { return data->size(); }
  bool empty() const { return data->empty(); }
  void push_back(const string& t) { data->push_back(t); }
  void pop_back();

  string& front();
  string& back();
  const string& front() const;
  const string& back() const;

private:
  shared_ptr<vector<string>> data;
  // throw <msg> if data[i] isn't valid
  void check(size_t i, const string& msg) const;
};

StrBlob::StrBlob():
  data(make_shared<vector<string>>()) {}

StrBlob::StrBlob(initializer_list<string> il):
  data(make_shared<vector<string>>(il)) {}

string& StrBlob::operator[](size_t i) {
  check(i, "index out of range");
  return(*data)[i];
}

const string& StrBlob::operator[](size_t i) const {
  check(i, "index out of range");
  return (*data)[i];
}

void StrBlob::check(size_t i, const string& msg) const {
  if (i>=data->size())
    throw out_of_range(msg);
}

string& StrBlob::front() {
  check(0, "front on empty StrBlob");
  return data->front();
}

string& StrBlob::back() {
  check(0, "back on empty StrBlob");
  return data->back();
}

const string& StrBlob::front() const {
  check(0, "front on empty StrBlob");
  return data->front();
}

const string& StrBlob::back() const {
  check(0, "back on empty StrBlob");
  return data->back();
}

void StrBlob::pop_back() {
  check(0, "pop back on empty StrBlob");
  data->pop_back();
}
// ---------------------------------------

class QueryResult;

class TextQuery {
public:
  // Constructors
  TextQuery(ifstream&);
  // process the word "element" to query it in the file
  QueryResult query(const string&) const;

private:
  StrBlob file; // lines of an input file
  // map each word to a set of lines
  map<string, shared_ptr<set<size_t>>> wm;  
};

class QueryResult {
friend ostream& print(ostream&, const QueryResult&);
public:
  // Constructor
  QueryResult(string s, shared_ptr<set<size_t>> p, StrBlob f):
    sought(s), lines(p), file(f) {}

private:
  string sought; // "element"...
  shared_ptr<set<size_t>> lines; // ...on which lines?
  StrBlob file; // lines of an input file
};

// Constructor of <TextQuery>
TextQuery::TextQuery(ifstream& is) {
  string text;
  while(getline(is, text)) {
    file.push_back(text);
    int n = file.size() - 1; // the current line number

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
    os << "\t(line " << num+1 << ") " << qr.file[num] << endl;
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
  ifstream infile("exercise12_30_input.txt");
  runQueries(infile);

  return 0;
}