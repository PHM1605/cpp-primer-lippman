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
  void add_to_Folders(const Message&); // add this <Message> to the set of Folders
  void remove_from_Folders(); // remove this <Message> from the set of Folders
};

int main() {
  return 0;
}