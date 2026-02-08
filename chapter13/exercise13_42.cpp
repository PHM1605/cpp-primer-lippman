// Test <TextQuery> and <QueryResult> using <StrVec>
#include <iostream>
#include <fstream>
#include <memory>
#include <set>
#include <map>

using namespace std;

// Replacement for vector<string>
class StrVec {
public:
  StrVec():
    elements(nullptr), first_free(nullptr), cap(nullptr) {}
  StrVec(const StrVec&); // copy constructor
  StrVec(const initializer_list<string>);
  StrVec& operator=(const StrVec&); // copy assignment
  ~StrVec(); // destructor

  void push_back(const string&);
  size_t size() const { return first_free-elements; }
  size_t capacity() const { return cap-elements; }
  void reallocate(); // get more space and copy existing elements
  // trigger reallocate() when there is no space left
  void chk_n_alloc() {
    if (size() == capacity())
      reallocate();
  }

private:
  static allocator<string> alloc;

  string* elements; // pointer to the 1st string in array
  string* first_free; // pointer to one-past-last-constructed
  string* cap; // pointer to one-past-capacity

  // destroy elements and free space
  void free();
};
allocator<string> StrVec::alloc;

class QueryResult;

class TextQuery {
public:
  // Constructors
  TextQuery(ifstream&);
  // query the word "element" from the file
  QueryResult query(const string&) const;

private:
  shared_ptr<StrVec> file;
  // map each word to a set of line-numberS
  map<string, shared_ptr<set<size_t>>> wm; 
};

class QueryResult {
private:
  string sought; // e.g. "element"
  shared_ptr<set<size_t>> lines; // "element" occurs in which lineS
  shared_ptr<StrVec> file; // 
};

// Definitions
// file: list of lines
TextQuery::TextQuery(ifstream& is): file(new StrVec) {
  string text;
  while(getline(is, text)) {
    file->push_back(text);
    int n = file->size() - 1; // current line number
  }
}

void StrVec::push_back(const string& s) {
  // make sure there is room for another element
  chk_n_alloc();
  // construct that element
  alloc.construct(first_free++, s);
}

void StrVec::reallocate() {
  // if size=0 => allocate 1
  // if size>0 => double the size
  auto newcapacity = size() ? 2*size() : 1;
  auto newdata = alloc.allocate(newcapacity);

  // move all elements from old array to new location
  auto dest = newdata;
  auto elem = elements;
  for (size_t i=0; i!=size(); ++i) {
    alloc.construct(dest++, std::move(*elem++)); // NOTE: move-constructor
  }
  // still, we must free the old ones
  free();
  // update old object to new elements
  elements = newdata;
  first_free = dest;
  cap = elements + newcapacity;
}

void StrVec::free() {
  if (elements) {
    // moving backward
    for (auto p=first_free; p!=elements; /*empty*/) {
      alloc.destroy(--p);
    }
    alloc.deallocate(elements, cap-elements);
  }
}

void runQueries(ifstream& infile) {
  // parse the .txt file
  TextQuery tq(infile);
}

int main() {
  ifstream infile("exercise13_42_input.txt");
  runQueries(infile);

  return 0;
}