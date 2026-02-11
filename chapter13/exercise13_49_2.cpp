// Create <Message> with "move-constructor" and "move-assignment"
#include <iostream>
#include <set>

using namespace std;

class Message; // forward declaration

class Folder {
public:
  Folder() = default;
  Folder(const Folder&);
  Folder& operator=(const Folder&);
  ~Folder();
  // Move constructor
  
private:
  set<Message*> messages;

  // add/remove Message to Folder
  void addMsg(Message* m) { messages.insert(m); }
  void remMsg(Message* m) { messages.erase(m); }
  // change parent Folders of all Messages
  void add_to_Messages(const Folder& f);
  void remove_from_Messages();
};

int main() {

}