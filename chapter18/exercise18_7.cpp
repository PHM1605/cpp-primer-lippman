// Define <Blob> and <BlobPtr> with "function-try-blocks"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

template<typename> class BlobPtr; // so that <BlobPtr> can access <data> member in <Blob>

template<typename T>
class Blob {
  friend class BlobPtr<T>;
public:
  Blob() try: data(make_shared<vector<T>>()) {
    cout << "Blob default constructor OK\n";
  } catch(const exception& e) {
    cerr << "Blob default constructor error: " << e.what() << endl;
    throw;
  }

  // NOTE: we FORCE ERROR here to check
  Blob(initializer_list<T> il) try: data(make_shared<vector<T>>(il)) {
    cout << "Blob init constructor OK\n";
    // FORCE ERROR
    throw runtime_error("Forced error inside Blob constructor");
  } catch(const exception& e) {
    cerr << "Caught in Blob constructor: " << e.what() << endl;
    throw;
  }

  size_t size() const { return data->size(); }
  void push_back(const T& t) {
    data->push_back(t);
  }

  T& back() {
    check(0, "back on empty Blob");
    return data->back();
  }

  T& operator[](size_t i) {
    check(i, "subscript out of range");
    return (*data)[i];
  }

private:
  shared_ptr<vector<T>> data;
  void check(size_t i, const string& msg) const {
    if (i>=data->size()) {
      throw out_of_range(msg);
    }
  }
};

template<typename T>
class BlobPtr {
public:
  BlobPtr(): curr(0) {}
  BlobPtr(Blob<T>& a, size_t sz=0) try:
    wptr(a.data), curr(sz) {
      cout << "BlobPtr constructor OK\n";
    } catch (const exception& e) {
      cerr << "BlobPtr constructor error: " << e.what() << endl;
      throw;
    }

  // dereference with error checking
  T& operator*() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
  }
private:
  size_t curr; // current position within array
  weak_ptr<vector<T>> wptr;
  // check if accessing an element is valid
  shared_ptr<vector<T>> check(size_t i, const string& msg) const {
    auto ret = wptr.lock();
    if (!ret)
      throw runtime_error("unbound BlobPtr");
    if (i>=ret->size())
      throw out_of_range(msg);
    return ret;
  }
};

int main() {
  try {
    cout << "Creating Blob...\n";
    Blob<int> b{1,2,3,4}; // will throw
    // these lines will NOT run
    cout << "Blob size: " << b.size() << endl;
    cout << "Last element: " << b.back() << endl;
  }
  catch(const exception& e) {
    cout << "Caught in main: " << e.what() << endl;
  }
  
  cout << "Program continues after exception.\n";
  return 0;
}