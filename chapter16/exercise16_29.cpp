// Rewrite <Blob> with <SharedPtr>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

// Deleters
struct DefaultDelete {
  template<typename T>
  void operator()(T* p) const { delete p; }
};
class DebugDelete {
public:
  DebugDelete(ostream& s=cerr): os(s) {}
  
  template<typename T>
  void operator()(T* p) const {
    os << "deleting shared_ptr\n";
    delete p;
  }
private:
  ostream& os;
};

struct ControlBlockBase {
  size_t count = 1;
  virtual void dispose() = 0;
  virtual ~ControlBlockBase() = default;
};

template<typename T, typename D>
struct ControlBlock: ControlBlockBase {
  ControlBlock(T* p, D d): ptr(p), deleter(d) {}
  
  void dispose() override { deleter(ptr); }

  T* ptr;
  D deleter;
};

template<typename T>
class SharedPtr {
public:
  template<typename D = DefaultDelete>
  SharedPtr(T* p=nullptr, D d=D()): ptr(p) {
    if (ptr)
      ctrl = new ControlBlock<T,D>(p,d);
    else 
      ctrl = nullptr;
  }
  SharedPtr(const SharedPtr& other):
    ptr(other.ptr), ctrl(other.ctrl) {
      if (ctrl)
        ++ctrl->count;
    }
  
  ~SharedPtr() {
    if (ctrl && --ctrl->count == 0) {
      ctrl->dispose();
      delete ctrl;
    }
  }

  T& operator*() { return *ptr; }
  T* operator->() const { return ptr; }
  size_t use_count() const {
    return ctrl ? ctrl->count : 0;
  }

private:
  T* ptr;
  ControlBlockBase* ctrl = nullptr;
};

template<typename T>
class Blob {
public:
  Blob(): data(new vector<T>(), DebugDelete()) {}
  Blob(initializer_list<T> il):
    data(new vector<T>(il), DebugDelete()) {}
  
  template<typename It>
  Blob(It b, It e):
    data(new vector<T>(b,e), DebugDelete()) {}

  size_t size() const { return data->size(); }
  bool empty() const { return data->empty(); }
  void push_back(const T& t) { data->push_back(t); }
  T& front() {
    check(0, "front on empty Blob");
    return data->front();
  }
  T& back() {
    check(0, "back on empty Blob");
    return data->back();
  }

private:
  SharedPtr<vector<T>> data;
  void check(size_t i, const string& msg) const {
    if (i>=data->size())
      throw out_of_range(msg);
  }
};

int main() {
  int ia[] = {0,1,2,3,4,5,6,7,8,9};
  vector<long> vi = {0,1,2,3,4,5,6,7,8,9};
  list<const char*> w = {"now", "is", "the", "time"};

  Blob<int> a1(begin(ia), end(ia));
  Blob<int> a2(vi.begin(), vi.end());
  Blob<string> a3(w.begin(), w.end());

  cout << "a1 front: " << a1.front() << "; back: " << a1.back() << endl;
  cout << "a2 front: " << a2.front() << "; back: " << a2.back() << endl;
  cout << "a3 front: " << a3.front() << "; back: " << a3.back() << endl;

  cout << "sizes: " << a1.size() << " " << a2.size() << " " << a3.size() << endl;

  return 0;
}