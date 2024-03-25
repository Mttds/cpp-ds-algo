#include <iostream>
#include <vector>

using namespace std;

template <typename T, int t>
class BTree {
  private:
    class Node {
    public:
        bool leaf;
        vector<T> keys;
        vector<Node*> children;

        Node(bool _leaf) : leaf(_leaf) {}

        int findKey(T key) {
            int idx = 0;
            while (idx < keys.size() && keys[idx] < key) {
                ++idx;
            }
            return idx;
        }

        void insertNonFull(T key) {
            int i = keys.size() - 1;
            if (leaf) {
                keys.push_back(T());
                while (i >= 0 && keys[i] > key) {
                    keys[i + 1] = keys[i];
                    i--;
                }
                keys[i + 1] = key;
            } else {
                while (i >= 0 && keys[i] > key) {
                    i--;
                }
                if (children[i + 1]->keys.size() == 2 * t - 1) {
                    splitChild(i + 1, children[i + 1]);
                    if (keys[i + 1] < key) {
                        i++;
                    }
                }
                children[i + 1]->insertNonFull(key);
            }
        }

        void splitChild(int i, Node* y) {
            Node* z = new Node(y->leaf);
            z->keys.resize(t - 1);
            if (!y->leaf) {
                z->children.resize(t);
            }
            for (int j = 0; j < t - 1; j++) {
                z->keys[j] = y->keys[j + t];
            }
            if (!y->leaf) {
                for (int j = 0; j < t; j++) {
                    z->children[j] = y->children[j + t];
                }
            }
            y->keys.resize(t - 1);
            if (!y->leaf) {
                y->children.resize(t);
            }
            children.insert(children.begin() + i + 1, z);
            keys.insert(keys.begin() + i, y->keys[t - 1]);
        }

        void traverse() {
            int i;
            for (i = 0; i < keys.size(); i++) {
                if (!leaf) {
                    children[i]->traverse();
                }
                cout << keys[i] << " ";
            }
            if (!leaf) {
                children[i]->traverse();
            }
        }
    };

    Node* root;

  public:
    BTree() {
        root = nullptr;
    }

    void insert(T key) {
        if (root == nullptr) {
            root = new Node(true);
            root->keys.push_back(key);
        } else {
            if (root->keys.size() == 2 * t - 1) {
                Node* s = new Node(false);
                s->children.push_back(root);
                s->splitChild(0, root);
                int i = 0;
                if (s->keys[0] < key) {
                    i++;
                }
                s->children[i]->insertNonFull(key);
                root = s;
            } else {
                root->insertNonFull(key);
            }
        }
    }

    void traverse() {
        if (root != nullptr) {
            root->traverse();
        }
    }
};
