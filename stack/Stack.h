#include <iostream>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* topNode;

public:
    Stack() : topNode(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
    }

    void pop() {
        if (isEmpty()) {
            std::cerr << "Error: Stack is empty. Cannot pop." << std::endl;
            return;
        }

        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }

    T top() const {
        if (isEmpty()) {
            std::cerr << "Error: Stack is empty. No top element." << std::endl;
            exit(EXIT_FAILURE);
        }

        return topNode->data;
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    size_t size() const {
        size_t count = 0;
        Node* current = topNode;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
};
