// We have class NoDefault that has a constructor that takes an int
// define class C that has a member of type NoDefault
class NoDefault {
public:
  NoDefault(int i);
};

class C {
public:
  C(): no_default(12) {};
private:
  NoDefault no_default;
};