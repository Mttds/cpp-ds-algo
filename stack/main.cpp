#include "Stack.h"

int main() {
    Stack<int> myStack;

    myStack.push(10);
    myStack.push(20);
    myStack.push(30);

    std::cout << "Top element: " << myStack.top() << std::endl;
    std::cout << "Stack size: " << myStack.size() << std::endl;

    myStack.pop();
    std::cout << "Top element after pop: " << myStack.top() << std::endl;
    std::cout << "Stack size after pop: " << myStack.size() << std::endl;

    return 0;
}
