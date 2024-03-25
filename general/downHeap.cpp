/* Heap represented as a binary tree of nodes instead of as an array */
/* g++ downHeap.cpp -o downHeap */

#include <iostream>
#include <string>

class Node {
public:
  int value;
  Node *left, *right;
  Node(int val = 0) { value = val; left = right = nullptr; }
  ~Node() {
    delete left;
    left = nullptr;
    delete right;
    right = nullptr;
  }
};

void downHeap(Node *n) {
  if (n == nullptr) {
    return;
  }

  Node* minNode = n;
  if (n->left != nullptr && n->left->value < minNode->value) {
    minNode = n->left;
  }

  if (n->right != nullptr && n->right->value < minNode->value) {
    minNode = n->right;
  }

  if (minNode != n) {
    std::swap(n->value, minNode->value);
    // recursively downHeap on the subtree where the value was swapped
    downHeap(minNode);
  }
}

void printTree(Node *n) {
  if (!n) return;
  std::cout << n->value << "(";
  printTree(n->left);
  std::cout << ")(";
  printTree(n->right);
  std::cout << ")";
}

int main() {
  Node *n = new Node(100);
  n->left = new Node(1);
  n->right = new Node(2);
  n->right->left = new Node(3);
  n->right->right = new Node(4);
  n->right->right->right = new Node(5);

  downHeap(n);

  std::cout << "Compact printout:" << std::endl;
  printTree(n);

  delete n;
  n = nullptr;

  return 0;
}
