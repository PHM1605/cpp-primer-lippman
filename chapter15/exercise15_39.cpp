// Text query revisited
#include <iostream>
#include <memory>
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class QueryResult; // forward declaration
// has: <lines> and a <set> of which word on which lines
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
  
  set<size_t>::iterator begin() { return lines->begin(); }
  set<size_t>::iterator end() { return lines->end(); }
  shared_ptr<vector<string>> get_file() { return file; }

private:
  string sought; // "element"...
  shared_ptr<set<size_t>> lines; // ... on which lines?
  shared_ptr<vector<string>> file; // lines of an input file
};

// definitions of <TextQuery>
TextQuery::TextQuery(ifstream& is): file(new vector<string>) {
  string text;
  while(getline(is, text)) {
    file->push_back(text);
    int n = file->size()-1; // current line number
    // read each line, each word into <map>
    istringstream line(text);
    string word;
    while (line >> word) {
      // convert "hair." or "hair," to "hair"
      word.erase(
        remove_if(word.begin(), word.end(), [](char c){ return ispunct(c); }),
        word.end()
      );
      // lines: alias to a <shared_ptr> to a set of line-numbers
      // nullptr if that "word" not exist
      auto& lines = wm[word];
      if (!lines)
        lines.reset(new set<size_t>);
      lines->insert(n); // add that line number
    }
  }
}

QueryResult TextQuery::query(const string& sought) const {
  // in case we don't find "sought"
  static shared_ptr<set<size_t>> nodata(new set<size_t>);
  // try to find "sought" in "map"
  auto loc = wm.find(sought);
  if (loc == wm.end())
    return QueryResult(sought, nodata, file);
  else
    return QueryResult(sought, loc->second, file);
}

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
  // to allow using private constructors
  friend Query operator~(const Query&);
  friend Query operator|(const Query&, const Query&);
  friend Query operator&(const Query&, const Query&);

public:
  Query(const string&); // builds a new <WordQuery>
  // calls it's wrapped <Query_base> (virtual->will be deeper) functions
  QueryResult eval(const TextQuery& t) const { 
    return q->eval(t); 
  }
  string rep() const { 
    return q->rep(); 
  }

private:
  // private constructor
  Query(shared_ptr<Query_base> query): q(query) {}
  shared_ptr<Query_base> q;
};

ostream& operator<<(ostream& os, const Query& query) {
  return os << query.rep();
}

// all private
class WordQuery: public Query_base {
  friend class Query; // to allow <Query> constructing a <WordQuery>
  WordQuery(const string& s):
    query_word(s) {}

  // define virtual functions
  QueryResult eval(const TextQuery& t) const {
    return t.query(query_word);
  }
  string rep() const { return query_word; }

  string query_word;
};

class NotQuery: public Query_base {
  friend Query operator~(const Query&); 
  NotQuery(const Query& q): query(q) {}

  // override 
  string rep() const { 
    return "~(" + query.rep() + ")";
  }
  QueryResult eval(const TextQuery&) const;

  Query query;
};

inline Query operator~(const Query& operand) {
  return shared_ptr<Query_base>(new NotQuery(operand));
}

class BinaryQuery: public Query_base {
protected:
  BinaryQuery(const Query&l, const Query& r, string s):
    lhs(l), rhs(r), opSym(s) {}

  // NOTE: abstract class; BinaryQuery doesn't define <eval>
  string rep() const {
    return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
  }

  Query lhs, rhs;
  string opSym; // name of operator
};

class AndQuery: public BinaryQuery {
  // to allow operator&() to create an <AndQuery>
  friend Query operator&(const Query&, const Query&);

  AndQuery(const Query& left, const Query& right):
    BinaryQuery(left, right, "&") {}

  // <AndQuery> inherits rep(); defines only eval()
  QueryResult eval(const TextQuery&) const;
};
inline Query operator&(const Query& lhs, const Query& rhs) {
  return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

class OrQuery: public BinaryQuery {
  // to allow operator|() to create an <OrQuery>
  friend Query operator|(const Query&, const Query&);
  OrQuery(const Query& left, const Query& right):
    BinaryQuery(left, right, "|") {}
  
  // <OrQuery> inherits rep(); defines eval() only
  QueryResult eval(const TextQuery&) const;
};
inline Query operator|(const Query& lhs, const Query& rhs) {
  return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

inline Query::Query(const string& s):
  q(new WordQuery(s)) {}

// Definitions
QueryResult OrQuery::eval(const TextQuery& text) const {
  // return <QueryResult> for each operand
  auto right = rhs.eval(text), left = lhs.eval(text);
  // set of lines from 1st-operand
  auto ret_lines = make_shared<set<size_t>>(left.begin(), left.end());
  // set of lines from 2ns-operand
  ret_lines->insert(right.begin(), right.end());
  
  return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult AndQuery::eval(const TextQuery& text) const {
  // return <QueryResult> for each operand
  auto right = rhs.eval(text), left = lhs.eval(text);
  // set of line-numbers
  auto ret_lines = make_shared<set<size_t>>();
  // intersection between 2 sets
  // <inserter>: create an <insert-iterator>
  // - 1st argument: which container we should insert to
  // - 2nd argument: which location on that container we should start
  set_intersection(
    left.begin(), left.end(),
    right.begin(), right.end(), 
    inserter(*ret_lines, ret_lines->begin())
  );
  return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult NotQuery::eval(const TextQuery& text) const {
  auto result = query.eval(text); // original query (without NOT)
  auto ret_lines = make_shared<set<size_t>>();
  // iterators to the set of with-"element"-lines
  auto orig_beg = result.begin(), orig_end = result.end();
  // loop over each line in files
  for(size_t n=0; n!=result.get_file()->size(); ++n) {
    // NOTE: set() is automatically sorted in ascending order
    // if that line is not yet in with-"element"-lines => insert
    if (orig_beg == orig_end || *orig_beg != n) {
      ret_lines->insert(n);
    } 
    // if that line equals the current-with-"element"-line => check next with-"element"-line
    else if (orig_beg != orig_end) {
      ++orig_beg;
    }
  }
  return QueryResult(rep(), ret_lines, result.get_file());
}

void print_query(Query& q, QueryResult& qr) {
   // display result
  cout << "Executing Query for: " << q << endl;
  cout << q << " occurs " << distance(qr.begin(), qr.end()) << " times\n";
  for (auto iter=qr.begin(); iter!=qr.end(); iter++) {
    cout << "(line " << *iter << ") " << (*qr.get_file())[*iter] << endl;
  }
  cout << endl;
}

int main() {
  // preprocess input text file
  ifstream infile("exercise15_39_input.txt");
  TextQuery tq(infile);
  // evaluate 
  Query q1 = Query("fiery") & Query("bird") | Query("wind");
  QueryResult qr1 = q1.eval(tq);
  print_query(q1, qr1);

  Query q2 = ~Query("Alice");
  QueryResult qr2 = q2.eval(tq);
  print_query(q2, qr2);

  Query q3 = Query("hair") | Query("Alice");
  QueryResult qr3 = q3.eval(tq);
  print_query(q3, qr3);

  Query q4 = Query("hair") & Query("Alice");
  QueryResult qr4 = q4.eval(tq);
  print_query(q4, qr4);

  return 0;
}