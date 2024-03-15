/**
 * TODO: A binary tree has nodes with at most 2 leaves, but is not ordered like a binary search tree
 *       where the left child has values less than the parent and the right child has values greater than the parent.
 *       To implement similarly to how the implementation of binary-search-tree/Dictionary.h is done
 */

#pragma once

template <typename T>
class BinaryTree {
  public:
    BinaryTree() : root_(nullptr) {}

  private:
    class TreeNode {
      public:
        T & data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(T & data) : data(data), left(nullptr), right(nullptr) { }
    };

    TreeNode *root_;
};

#include "BinaryTree.cpp"
