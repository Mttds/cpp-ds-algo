#include "btree.cpp"

int main() {
    BTree<int, 3> tree;

    // Insert some values
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);
    tree.insert(30);
    tree.insert(7);
    tree.insert(17);

    // Print the tree
    tree.traverse();

    return 0;
}
