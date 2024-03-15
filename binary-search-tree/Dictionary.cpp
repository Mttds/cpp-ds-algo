#include "Dictionary.h"

template <typename K, typename D>
const D & Dictionary<K, D>::find(const K & key) {
  TreeNode *& node = _find(key, head_);

  if (node == nullptr) {
    throw std::runtime_error("Key not found");
  }

  return node->data;
}

template <typename K, typename D>
typename Dictionary<K, D>::TreeNode *& Dictionary<K, D>::_find(const K & key, TreeNode *& cur) const {
  if (cur == nullptr) {
    return cur;
  } else if (key == cur->key) {
    return cur;
  } else if (key < cur->key) {
    return _find(key, cur->left);
  } else if (key > cur->key) {
    return _find(key, cur->right);
  } else {
    return cur; // should never happen, but prevents compiler warning control reaches end of non-void function [-Wreturn-type]
  }
}

template <typename K, typename D>
void Dictionary<K, D>::insert(const K & key, const D & data) {
  TreeNode *& node = _find(key, head_);
  node = new TreeNode(key, data);
}


template <typename K, typename D>
const D& Dictionary<K, D>::remove(const K& key) {
  TreeNode*& node = _find(key, head_);

  if (!node) {
    throw std::runtime_error("error: remove() used on non-existent key");
  }

  return _remove(node);
}

template <typename K, typename D>
const D& Dictionary<K, D>::_remove(TreeNode*& node) {
  if (!node) {
    throw std::runtime_error("error: _remove() used on non-existent key");
  }

  // Zero child remove:
  if (node->left == nullptr && node->right == nullptr) {
    // Peek at the data referred to by the node so we can return a reference
    // to the data later, after the tree node itself is already gone.
    const D& data = node->data;
    // The node is a leaf, so it has no descendants to worry about.
    // We can just delete it. (The slides originally showed "delete(node)".
    // Note that the syntax for "delete" is like an operator, not a function,
    // so it's not necessary to put the () when you use it.)
    delete node;
    // It's very important to set "node" to nullptr here. The parent is still
    // holding this same pointer, so we must mark that the child is gone.
    node = nullptr;
    return data;
  }
  // One-child (left) remove
  else if (node->left != nullptr && node->right == nullptr) {
    // Similar to the previous case, except that we need to remap the "node"
    // pointer to point to the node's child, so that the parent of the node
    // being deleted will retain its connection to the rest of the tree
    // below this point.
    const D& data = node->data;
    //TreeNode* temp = node;
    node = node->left;
    //delete temp;
    return data;
  }
  // One-child (right) remove
  else if (node->left == nullptr && node->right != nullptr) {
    // This case is symmetric to the previous case.
    const D& data = node->data;
    //TreeNode* temp = node;
    node = node->right;
    //delete temp;
    return data;
  }
  // Two-child remove
  else {
    // Find the IOP (in-order predecessor) of the current node.
    TreeNode*& iop = _iop(node);

    // Since this is the two-child remove case, we know that some in-order
    // predecessor does exist, so the _iop_of lookup should not have failed.
    if (!iop) {
      throw std::runtime_error("error in two-child remove: IOP not found");
    }

    // Swap the node to remove and the IOP.
    // (This function changes the pointers that are passed in-place so that
    //  it can alter the tree structure itself, but afterwards you don't
    //  know what the pointers point to exactly, depending on what happened.
    //  Therefore you shouldn't reuse these pointers in the current function
    //  after calling this. To make things easier, _swap_nodes will return
    //  a pointer, by reference, that is the updated pointer in the tree
    //  that is now pointing to the same node we gave as the first argument,
    //  so we can do more work on that node afterwards.)
    TreeNode*& moved_node = _swap(node, iop);

    // Note that we do not use the original "node" and "iop" pointers by
    // name after this point. Assume they are invalid now.

    // Recurse to remove the original targeted node at its updated position.
    return _remove(moved_node);
  }
}

template <typename K, typename D>
typename Dictionary<K, D>::TreeNode*& Dictionary<K, D>::_iop(TreeNode*& cur) const {

  // We want to find the in-order predecessor of "cur",
  // which is the right-most child of the left subtree of cur.

  if (!cur) {
    // If cur is nullptr, this is an error case.
    // Just return cur by reference. (Since cur has the value of nullptr,
    // we can check for that result.)
    return cur;
  }
  
  if (!(cur->left)) {
    // If cur has no left child, this is an error case.
    // Just return cur->left by reference. (Since cur->left has the value of
    // nullptr, we can check for that result.)
    return cur->left;
  }

  return _rightmost_of(cur->left);
}

template <typename K, typename D>
typename Dictionary<K, D>::TreeNode*& Dictionary<K, D>::_rightmost_of(TreeNode*& cur) const {

  // Base case 1: If cur is null, then just return it by reference.
  // (Since cur has the value of nullptr, we can check for that result.)
  if (!cur) return cur;

  // Base case 2: So far, we know cur is not null. Now, if cur does not have
  // a right child, then cur is the rightmost, so return cur by reference.
  if (!(cur->right)) return cur;

  // General case: The cur pointer is not null, and it does have a right
  // child, so we should recurse to the right and return whatever we get.
  return _rightmost_of(cur->right);
}

template <typename K, typename D>
typename Dictionary<K, D>::TreeNode*& Dictionary<K, D>::_swap(TreeNode*& node1, TreeNode*& node2) {
  // We need to swap the logical positions of these two nodes in the tree,
  // but this can be hard if one of the nodes is a child of the other. Then
  // one of the nodes holds the other actual pointer we're changing, so the
  // rewiring is a little complicated, and since we passed in these pointers
  // by reference to edit them in-place in the tree, we also end up with the
  // original argument variables becoming dangerous to reuse any further
  // outside of this function, where we made the call: These pointers no
  // longer refer to the nodes we originally thought. As a result, we need
  // to return by reference a pointer to where node1 can still be found.
  // (Again, if you want to track the new locations of both nodes, you would
  //  need to extend the return type of this function somehow, perhaps by
  //  returning a std::pair of references to pointers.)

  // These are value copies of the pointer arguments, so they hold copies
  // of the actual addresses that we are pointing to. We need to record
  // these, because when we start changing the pointers below, we'll lose
  // track of these original addresses.
  TreeNode* orig_node1 = node1;
  TreeNode* orig_node2 = node2;

  if (node1->left == node2) {
    // When node1 has node2 as its left child...

    // The right child pointers are easy to handle.
    // We can directly swap them.
    std::swap(node1->right, node2->right);

    // Now we have to deal with the left child pointers, and it's
    // complicated. We need to be very careful about the order of changes.
    // The easiest way to see how this works is draw a diagram of the
    // original nodes and pointers, and see how the pointers have to be
    // redirected.

    // Make "node1" take its leftmost grandchild as its left child.
    // The next line also affects the actual "node2" pointer, implicitly,
    // so we won't try to use the "node2" pointer after this; it will no
    // longer point to the original "node2" node that we would expect from
    // the naming.
    node1->left = orig_node2->left;
    // Now the original node2 needs to take the original node1 as its left
    // child.
    orig_node2->left = node1;
    // Now the actual node1 pointer should point to the object that was
    // the original node2.
    node1 = orig_node2;

    // The node position swap is done, but the node1 and node2 arguments
    // themselves haven't been swapped! We can't do that in this case.

    // This is the actual pointer in the tree that is now pointing to what
    // was our original node1 object, so return it by reference.
    return node1->left;
  }
  else if (node1->right == node2) {
    std::swap(node1->left, node2->left);
    node1->right = orig_node2->right;
    orig_node2->right = node1;
    node1 = orig_node2;
    return node1->right;
  }
  else if (node2->left == node1) {
    std::swap(node2->right, node1->right);
    node2->left = orig_node1->left;
    orig_node1->left = node2;
    node2 = orig_node1;
    return node2->left;
  }
  else if (node2->right == node1) {
    std::swap(node2->left, node1->left);
    node2->right = orig_node1->right;
    orig_node1->right = node2;
    node2 = orig_node1;
    return node2->right;
  }
  else {
    std::swap(node1->left, node2->left);
    std::swap(node1->right, node2->right);
    std::swap(node1, node2);

    // This is the actual pointer in the tree that is now pointing to what
    // was our original node1 object, so return it by reference.
    return node2;
  }
}
