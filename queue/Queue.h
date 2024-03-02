#include <iostream>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* frontNode;
    Node* rearNode;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            std::cerr << "Error: Queue is empty. Cannot dequeue." << std::endl;
            return;
        }

        Node* temp = frontNode;
        frontNode = frontNode->next;
        delete temp;

        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
    }

    T front() const {
        if (isEmpty()) {
            std::cerr << "Error: Queue is empty. No front element." << std::endl;
            exit(EXIT_FAILURE);
        }

        return frontNode->data;
    }

    bool isEmpty() const {
        return frontNode == nullptr;
    }

    size_t size() const {
        size_t count = 0;
        Node* current = frontNode;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
};
