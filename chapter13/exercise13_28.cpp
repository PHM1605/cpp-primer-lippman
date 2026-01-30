// <BinaryTree> and <TreeNode>
#include <iostream>

using namespace std;

class TreeNode {
public:
  // default constructor
  TreeNode() = default;
  // value constructor
  TreeNode(const string& s, int c = 1):
    value(s), count(c) {}
  // copy constructor: deep copy
  TreeNode(const TreeNode& rhs):
    value(rhs.value), count(rhs.count),
    left(rhs.left ? new TreeNode(*rhs.left): nullptr),
    right(rhs.right ? new TreeNode(*rhs.right): nullptr) {}

  // copy assignment: deep copy


  ~TreeNode() {
    delete left;
    delete right;
  }

  void print(int depth=0) {
    cout << string(depth*2, ' ') << value << " (" << count << ")\n";
    if (left)
      left->print(depth+1);
    if (right)
      right->print(depth+1);
  }

private:
  string value;
  int count; // how many times this "string" appears in the <Tree>
  TreeNode* left = nullptr;
  TreeNode* right = nullptr;

  friend class BinStrTree;
};

class BinStrTree {
public:
  // Default constructor
  BinStrTree() = default;
  // Copy constructor
  BinStrTree(const BinStrTree& rhs):
    root(rhs.root ? new TreeNode(*rhs.root) : nullptr) {}
  // Copy assignment
  BinStrTree& operator=(const BinStrTree& rhs) {
    // avoid self-assignment first
    if (this == &rhs)
      return *this;
    // delete old root
    delete root;
    // create new root to assign
    root = rhs.root ? new TreeNode(*rhs.root) : nullptr;
    return *this;
  }
  // Destructor
  ~BinStrTree() {
    delete root;
  }

  void build_sample() {
    root = new TreeNode("m");
    root->left = new TreeNode("c");
    root->right = new TreeNode("t");
  }

  void print() {
    if (root)
      root->print();
  }

private:
  TreeNode* root = nullptr;
};

int main() {
  BinStrTree t1;
  t1.build_sample();

  BinStrTree t2 = t1; // copy-constructor
  BinStrTree t3; 
  t3 = t1; // copy-assignment

  cout << "t1:\n";
  t1.print();

  cout << "\nt2:\n";
  t2.print();

  cout << "\nt3:\n";
  t3.print();

  return 0;
}