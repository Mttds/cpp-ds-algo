/* g++ -o height_tree height_tree.cpp */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

class Node {
public:
  int height;
  Node *left, *right;
  Node() { height = -1; left = right = nullptr; }
  ~Node() {
    delete left;
    left = nullptr;
    delete right;
    right = nullptr;
  }
};

void computeHeight(Node *n) {
  if (n == nullptr) {
    // height is already set to -1
    return;
  }

  // recursively compute heights of left and right subtrees
  computeHeight(n->left);
  computeHeight(n->right);

  // get the heights of left and right subtrees
  int heightLeft = (n->left == nullptr) ? -1 : n->left->height;
  int heightRight = (n->right == nullptr) ? -1 : n->right->height;

  // geight of the current node is the maximum height of its subtrees plus 1
  n->height = std::max(heightLeft, heightRight) + 1;
}

void printTree(const Node *n) {
  if (!n) return;
  std::cout << n->height << "(";
  printTree(n->left);
  std::cout << ")(";
  printTree(n->right);
  std::cout << ")";
}

int main() {
  Node *n = new Node();
  n->left = new Node();
  n->right = new Node();
  n->right->left = new Node();
  n->right->right = new Node();
  n->right->right->right = new Node();

  computeHeight(n);

  printTree(n);
  std::cout << std::endl << std::endl;

  delete n;
  n = nullptr;

  return 0;
}
