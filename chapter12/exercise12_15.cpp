// Write a function that uses <shared_ptr> to manage a <connection>
// NOTE: using <lambda>
#include <iostream>
#include <memory>

using namespace std;

// represents what we are connecting to
struct destination {
  string name;
};

// info needed to use the connection; do NOT has a destructor
struct connection {
  string name;
};

// opens connection
connection* connect(destination* d) {
  cout << "connecting to " << d->name << endl;
  return new connection{d->name};
} 

// close the given connection
void disconnect(connection *p) {
  cout << "disconnecting from " << p->name << endl;
  delete p;
} 

void f(destination& d) {
  // get a connection; must remember to close it when done
  connection* c = connect(&d);
  shared_ptr<connection> p(c, [](connection* p) {
    cout << "disconnecting from " << p->name << endl;
    delete p;
  });
  // use the connection
  cout << "using connection to " << p->name << endl;
  // when f exits, even with an exception, connection will be closed
}

int main() {
  destination d{"server_1"};
  f(d);

  return 0;
}