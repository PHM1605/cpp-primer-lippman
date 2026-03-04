// Text query revisited
#include <iostream>
#include <memory>
#include <set>
#include <vector>
#include <map>

using namespace std;

class QueryResult; // forward declaration
class TextQuery {
public:
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
  QueryResult(string s, shared_ptr<set<size_t>>p, shared_ptr<vector<string>> f):
    sought(s), lines(p), file(f) {}

private:
  string sought; // "element"...
  shared_ptr<set<size_t>> lines; // ... on which lines?
  shared_ptr<vector<string>> file; // lines of an input file
};

// definitions of <TextQuery>


class Query_base {
  friend class Query;
protected:
  virtual ~Query_base() = default;

private:
  virtual QueryResult eval(const TextQuery&) const = 0;
  // return a <string> representation of the query
  virtual string rep() const = 0;
};

class Query {
public:
  Query(const string&);

  string rep() const { return q->rep(); }
private:
  shared_ptr<Query_base> q;
};

ostream& operator<<(ostream& os, const Query& query) {
  return os << query.rep();
}

int main() {
  string sought1("hair");
  string sought2("Alice");
  Query andq = Query(sought1) & Query(sought2);

  cout << andq << endl;
  return 0;
}