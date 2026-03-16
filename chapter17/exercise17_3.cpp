// Rewrite <TextQuery> to use <tuple> instead of <QueryResult>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <map>
#include <set>

using namespace std;

class TextQuery {
public:
  using Result = tuple<
    string, // word "elem"
    shared_ptr<set<size_t>>, // appears on which lines
    shared_ptr<vector<string>> // all lines in file
    >;

  TextQuery(ifstream&);
  Result query(const string&) const;

private:
  shared_ptr<vector<string>> file; // vector of lines
  map<string, shared_ptr<set<size_t>>> wm; // word "elem" appears on which lines
};

TextQuery::TextQuery(ifstream& is): file(new vector<string>) {
  string line;
  while(getline(is, line)) {
    file->push_back(line);
    int n = file->size()-1; // last line
    
    istringstream line_ss(line); 
    string word;
    while(line_ss >> word) {
      auto& lines = wm[word];
      // if set of ints not yet exists
      if (!lines)
        lines.reset(new set<size_t>);
      // if set of ints exists
      lines->insert(n);
    }
  }
}

TextQuery::Result TextQuery::query(const string& sought) const {
  static shared_ptr<set<size_t>> nodata(new set<size_t>);
  auto loc = wm.find(sought);
  // if cannot find that word in <map>
  if (loc == wm.end()) {
    return make_tuple(sought, nodata, file);
  } 
  // if that word already exists
  else {
    return make_tuple(sought, loc->second, file);
  }
}

ostream& print(ostream& os, const TextQuery::Result& qr) {
  const auto& sought = get<0>(qr);
  const auto& lines = get<1>(qr);
  const auto& file = get<2>(qr);

  os << sought << " occurs " << lines->size() << " " << (lines->size()>1?"times":"time") << endl;
  for (auto num: *lines) {
    os << "\t(line " << num+1 << ") " << (*file)[num] << endl;
  }
  return os;
}

void runQueries(ifstream& infile) {
  TextQuery tq(infile);
  while (true) {
    cout << "enter the word to look for, or q to quit: ";
    string inp_word;
    if (!(cin>>inp_word) || inp_word=="q")
      break;
    print(cout, tq.query(inp_word)) << endl;
  }  
}

int main() {
  ifstream infile("exercise17_3_input.txt");
  runQueries(infile);

  return 0;
}