// Write a <Folder> and <Message> class
#include <iostream>
#include <set>

using namespace std;

class Message;

class Folder {
  friend class Message;
  friend void swap(Message&, Message&);

public:
  Folder() = default;
  Folder(const Folder&);
  Folder& operator=(const Folder&);
  ~Folder();

private:
  set<Message*> messages;
  
  void addMsg(Message* m) { messages.insert(m); }
  void remMsg(Message* m) { messages.erase(m); }
  // change parent Folder of all Messages
  void add_to_Messages(const Folder& f);
  void remove_from_Messages();
};

class Message {
  friend class Folder;
  friend void swap(Message&, Message&); 
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

// copy assignment
Message& Message::operator=(const Message& rhs) {
  // remove left-hand message from all folders
  remove_from_Folders();
  contents = rhs.contents;
  folders = rhs.folders;
  add_to_Folders(rhs);
  return *this;
}

// destructor of Message
Message::~Message() {
  remove_from_Folders();
}

void Folder::remove_from_Messages() {
  for (auto m: messages) {
    m->folders.erase(this);
  }
  messages.clear();
}

// destructor of Folder
Folder::~Folder() {
  remove_from_Messages();
}

void swap(Message& lhs, Message& rhs) {
  using std::swap;
  // remove left-hand-message
  for (auto f: lhs.folders) {
    f->remMsg(&lhs);
  }
  // remove right-hand-message
  for (auto f: rhs.folders) {
    f->remMsg(&rhs);
  }
  // swap two messages
  swap(lhs.folders, rhs.folders);
  swap(lhs.contents, rhs.contents);
  // add messages to corresponding folders
  for (auto f: lhs.folders)
    f->addMsg(&lhs);
  for (auto f: rhs.folders)
    f->addMsg(&rhs);
}

int main() {
  Message m1("hello");
  Message m2("world");

  Folder f1;
  Folder f2;

  // f1: only has m1
  // f2: has m1 and m2
  m1.save(f1);
  m1.save(f2);
  m2.save(f2);

  return 0;
}