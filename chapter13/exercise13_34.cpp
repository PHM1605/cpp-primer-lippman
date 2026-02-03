// Write a <Folder> and <Message> class
#include <iostream>
#include <set>

using namespace std;

class Folder {

};

class Message {
friend class Folder;
public:
  // constructors
  explicit Message(const string& str = ""):
    contents(str) {}
  Message(const Message&); 
  Message& operator=(const Message&);
  // destructor
  ~Message();

  // add this <Message> to <Folder> set of messages
  void save(Folder&);
  // remove this <Message> from <Folder> set of messages
  void remove(Folder&);

private:
  string contents; // Message text
  set<Folder*> folders; // Folders that has this message
  void add_to_Folders(const Message&); // add this <Message> to ALL Folders
  void remove_from_Folders(); // remove this <Message> from ALL Folders
};

void Message::save(Folder& f) {
  folders.insert(&f); // add current folder to message's folders
  f.addMsg(this);  // add this message to folder's messages
}

void Message::remove(Folder& f) {
  folders.erase(&f); // remove current folder from message's folders
  f.remMsg(this); // remove this message from folder's messages
}

// add current message to ALL folders
void Message::add_to_Folders(const Message& m) {
  for (auto f: m.folders) {
    f->addMsg(this);
  }
}

// remove current message from ALL folders
void Message::remove_from_Folders() {
  for (auto f: folders) {
    f->remMsg(this);
  }
}

// copy constructor
Message::Message(const Message& m):
  contents(m.contents), folders(m.folders) // copy the set of pointers
{
  add_to_Folders(m); // add this message to all Folders
}

// destructor
Message::~Message() {
  remove_from_Folders();
}

int main() {
  return 0;
}