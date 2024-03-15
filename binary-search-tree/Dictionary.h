/* Implements a Binary Search Tree */

#pragma once

// so we can throw std::runtime_error in some cases.
#include <stdexcept>
// for the std::swap function
#include <utility>
// std::cout from <iostream>.
#include <iostream>

template <typename K, typename D>
class Dictionary {
  public:
    Dictionary() : head_(nullptr) {};
    const D& find(const K& key);
    void insert(const K& key, const D& data);
    const D& remove(const K& key);

    bool empty() const {
      // If the head_ pointer is null, returns true. Else, returns false.
      // (This happens implicitly because the value of head_ is cast to
      // bool and logically negated.)
      return !head_;
    }

    void printInOrder() {
      _printInOrder(head_);
    }

    // clear_tree: Remove the head item until the tree is empty.
    void clear_tree() {
      while (head_) {
        // As long as the head pointer isn't null, we can just look at
        // what the key is and call remove based on that.
        remove(head_->key);
      }
    }

    // Destructor: We just clear the tree.
    // This is public but you shouldn't call it directly. It gets called
    // when your tree is destroyed, either when you use "delete" on a tree
    // stored on the heap or when a tree stored on the stack goes out of
    // scope.
    ~Dictionary() {
      clear_tree();
    }

  private:
    class TreeNode {
      public:
        const K & key;
        const D & data;
        TreeNode *left;
        TreeNode *right;

        TreeNode(const K & key, const D & data) : key(key), data(data), left(nullptr), right(nullptr) {}
    };
  
    TreeNode* head_;

    TreeNode*& _find(const K& key, TreeNode*& cur) const;
    const D& _remove(TreeNode*& node);
    // _remove relies on the following three functions.
    TreeNode*& _iop(TreeNode*& cur) const;
    TreeNode*& _rightmost_of(TreeNode*& cur) const;
    TreeNode*& _swap(TreeNode*& node1, TreeNode*& node2);

    // printInOrder: Print the tree contents to std::cout using an in-order
    // traversal. The "_printInOrder" version is for internal use by the
    // public wrapper function "printInOrder".
    void _printInOrder(TreeNode* node) {
      // Base case: if node is nullptr, then print a space and return.
      if (!node) {
        std::cout << " ";
        return;
      }
      else {
        // Recurse left:
        _printInOrder(node->left);
        // Print this node:
        std::cout << "[" << node->key << " : " << node->data << "]";
        // Recurse right:
        _printInOrder(node->right);
      }
    }
};

#include "Dictionary.cpp"
