#include "Queue.h"

int main() {
    Queue<int> myQueue;

    myQueue.enqueue(10);
    myQueue.enqueue(20);
    myQueue.enqueue(30);

    std::cout << "Front element: " << myQueue.front() << std::endl;
    std::cout << "Queue size: " << myQueue.size() << std::endl;

    myQueue.dequeue();
    std::cout << "Front element after dequeue: " << myQueue.front() << std::endl;
    std::cout << "Queue size after dequeue: " << myQueue.size() << std::endl;

    return 0;
}
