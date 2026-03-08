// Extend the <Blob> to take iterators of a typename of <It>
#include <iostream>
#include <vector>
#include <memory>
#include <list>

using namespace std;

template<typename T>
class Blob {
public:
  Blob();
  Blob(initializer_list<T> il);
  // NEW: constructor with 2 iterators
  template <typename It>
  Blob(It b, It e);

  size_t size() const { return data->size(); }
  bool empty() const { return data->empty(); }
  void push_back(const T& t) { data->push_back(t); }
  void pop_back();
  T& front();
  T& back();

private:
  shared_ptr<vector<T>> data;
  void check(size_t i, const string& msg) const;
};

template<typename T>
Blob<T>::Blob():
  data(make_shared<vector<T>>()) {}

template<typename T>
Blob<T>::Blob(initializer_list<T> il):
  data(make_shared<vector<T>>(il)) {}

// NEW: constructor from 2 generic iterators
template<typename T>
template<typename It>
Blob<T>::Blob(It b, It e):
  data(make_shared<vector<T>>(b,e)) {}

template<typename T>
void Blob<T>::check(size_t i, const string& msg) const {
  if (i>=data->size())
    throw out_of_range(msg);
}

template<typename T>
T& Blob<T>::front() {
  check(0, "front on empty Blob");
  return data->front();
}

template<typename T>
T& Blob<T>::back() {
  check(0, "back on empty Blob");
  return data->back();
}

int main() {
  int ia[] = {0,1,2,3,4,5,6,7,8,9};
  vector<long> vi = {0,1,2,3,4,5,6,7,8,9};
  list<const char*> w = {"now", "is", "the", "time"};

  Blob<int> a1(begin(ia), end(ia));
  Blob<int> a2(vi.begin(), vi.end());
  Blob<string> a3(w.begin(), w.end());

  // print something to check
  cout << "a1 front: " << a1.front() << "; back: " << a1.back() << endl;
  cout << "a2 front: " << a2.front() << "; back: " << a2.back() << endl;
  cout << "a3 front: " << a3.front() << "; back: " << a3.back() << endl;

  cout << "sizes: " << a1.size() << " " << a2.size() << " " << a3.size() << endl;

  return 0;
}