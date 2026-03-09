// Write your own version of <shared_ptr> and <unique_ptr>
#include <iostream>

using namespace std;

struct DefaultDelete{
  template<typename T>
  void operator()(T* p) const { delete p; }
};

class DebugDelete {
public:
  DebugDelete(ostream& s = cerr): os(s) {}
  // function operator
  template<typename T>
  void operator()(T* p) const {
    os << "deleting shared_ptr" << endl;
    delete p;
  }
private:
  ostream& os;
};

// unique_ptr clone: template type of deleter needed
template<typename T, typename D=DefaultDelete>
class UniquePtr {
public:
  UniquePtr(T* p, D d=D()):
    ptr(p), del(d) {}
  ~UniquePtr() { if (ptr) del(ptr); }

  // disable copy
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr& operator=(const UniquePtr&) = delete;
  // allow moving
  UniquePtr(UniquePtr&& other):
    ptr(other.ptr), del(std::move(other.del)) {
      other.ptr = nullptr;
    }

  T& operator*() { return *ptr; }
  T* operator->() const { return ptr; }

private:
  T* ptr;
  D del;
};

struct ControlBlockBase {
  size_t count = 1;
  virtual void dispose() = 0;
  virtual ~ControlBlockBase() = default;
};

template<typename T, typename D>
struct ControlBlock: public ControlBlockBase {
  ControlBlock(T* p, D d): ptr(p), deleter(d) {}
  void dispose() override { deleter(ptr); }

  T* ptr;
  D deleter;
};

template<typename T>
class SharedPtr {
public:
  // new constructor 
  template<typename D=DefaultDelete>
  SharedPtr(T* p = nullptr, D d=D()): ptr(p) {
    if (ptr)
      ctrl = new ControlBlock<T,D>(p,d);
    else 
      ctrl = nullptr;
  }
  // copy constructor => increase <count>
  SharedPtr(const SharedPtr& other):
    ptr(other.ptr), ctrl(other.ctrl) {
      if (ctrl) ++ctrl->count;
    }
  
  ~SharedPtr() {
    if (ctrl && --ctrl->count == 0) {
      ctrl->dispose();
      delete ctrl;
    }
  }

  size_t use_count() const {
     return ctrl ? ctrl->count : 0;
  }

  T& operator*() { return *ptr; }
  T* operator->() const { return ptr; }

private:
  T* ptr;
  ControlBlockBase* ctrl; // can point to ANY deleter ControlBlock<T,D1> or ControlBlock<T,D2>
};

struct Foo {
  Foo() { cout << "Foo constructed\n"; }
  ~Foo() { cout << "Foo destroyed\n"; }
};

int main() {
  cout << "\n=== UniquePtr default deleter ===\n";
  {
    UniquePtr<Foo> p(new Foo);
  }

  cout << "\n=== UniquePtr DebugDelete ===\n";
  {
    UniquePtr<Foo, DebugDelete> p(new Foo, DebugDelete());
  }

  cout << "\n=== SharedPtr DebugDelete ===\n";
  {
    SharedPtr<Foo> p(new Foo, DebugDelete());
    SharedPtr<Foo> p2 = p;
    cout << "use_count = " << p.use_count() << endl;
  }

  cout << "\nend of program\n";

  return 0;
}