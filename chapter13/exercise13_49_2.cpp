// Create <Message> with "move-constructor" and "move-assignment"
#include <iostream>
#include <set>

using namespace std;

class Message; // forward declaration

class Folder {
  friend class Message;
public:
  Folder() = default;
  Folder(const Folder&);
  Folder& operator=(const Folder&);
  ~Folder();
  
private:
  set<Message*> messages;

  // add/remove Message to Folder
  void addMsg(Message* m); 
  void remMsg(Message* m); 
  // change parent Folders of all Messages
  void add_to_Messages(const Folder& f);
  void remove_from_Messages();
};

class Message {
  friend class Folder;
public:
  // constructor with string
  explicit Message(const string& str = ""):
    contents(str) {}
  Message(const Message&); // copy-constructor
  Message& operator=(const Message&); // assignment operator
  ~Message(); // destructor

  void save(Folder&); // add this Message to list of Messages of Folder argument
  void remove(Folder&); // remove this Message from list of Messages of Folder argument

  // Move constructor
  Message(Message &&m);
  // Move assignment
  Message& operator=(Message&& rhs);

private:
  string contents;
  set<Folder*> folders;

  // operators
  void add_to_Folders(const Message&); // add this Message to all Folders of argument Message
  void remove_from_Folders(); // remove this Message from all Folders
  void addFolder(Folder* f) { folders.insert(f); } // add a Folder to this Message's owners
  void remFolder(Folder* f) { folders.erase(f); } // remove a Folder from this Message's owners

  // NEW: move Folders linking from the Message-argument to THIS
  void move_Folders(Message*);
};

// =============== FOLDER =========================
Folder::Folder(const Folder& f):
  messages(f.messages) {
  add_to_Messages(f);
}

Folder::~Folder() {
  remove_from_Messages();
}

// add/remove Message to Folder
void Folder::addMsg(Message* m) {
  messages.insert(m);
}
void Folder::remMsg(Message* m) {
  messages.erase(m);
}

// add this Folder to the set of Messages of the argument Folder
void Folder::add_to_Messages(const Folder& f) {
  for (auto m: f.messages) {
    m->folders.insert(this);
  }
}
// remove this Folder from current list of Messages
void Folder::remove_from_Messages() {
  for (auto m: messages) 
    m->remFolder(this);
}
// ==============================================

// ================== MESSAGE ====================
// Destructor
Message::~Message() {
  remove_from_Folders();
}

// Move constructor
Message::Message(Message &&m):
  contents(std::move(m.contents)) {
  move_Folders(&m);
}
// Move assignment
Message& Message::operator=(Message &&rhs) {
  if (this != &rhs) {
    remove_from_Folders();
    contents = std::move(rhs.contents);
    move_Folders(&rhs);
  }
  return *this;
}

// Aux functions
// add this Message to all Folders of argument Message
void Message::save(Folder& f) {
  folders.insert(&f);
  f.addMsg(this);
}
// remove this Message from list of Messages of Folder argument
void Message::remove(Folder& f) {
  folders.erase(&f);
  f.remMsg(this);
}

// move Folders linking from the Message-argument to THIS
void Message::move_Folders(Message* m) {
  folders = std::move(m->folders);
  for (auto f: folders) {
    f->remMsg(m);
    f->addMsg(this);
  }
  m->folders.clear();
}

// add current Message to all Folders of the parameter Message
void Message::add_to_Folders(const Message& m) {
  for (auto f: m.folders) {
    f->addMsg(this);
  }
}

// remove current Message from all Folders of THIS 
void Message::remove_from_Folders() {
  for (auto f: folders) {
    f->remMsg(this);
  }
  folders.clear();
}
// =================================================


int main() {
  cout << "\n--- Create folder and message ---\n";
  Folder f1;
  Message m1("hello");
  
  m1.save(f1);

  cout << "\n--- Move constructor ---\n";
  Message m2(std::move(m1));

  cout << "\n--- Move assignment ---\n";
  Message m3("world");
  m3 = std::move(m2);

  cout << "\n--- End of main ---\n";

  return 0;
}