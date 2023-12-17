#include <iostream>

class Stack {
private:
    static const int MAX_SIZE = 100;
    int arr[MAX_SIZE];
    int top;

public:
    Stack() : top(-1) {}

    bool isEmpty() const {
        return top == -1;
    }

    bool isFull() const {
        return top == MAX_SIZE - 1;
    }

    void push(int value) {
        if (isFull()) {
            std::cerr << "Stack overflow. Cannot push element onto a full stack." << std::endl;
            return;
        }

        arr[++top] = value;
        std::cout << "Pushed " << value << " onto the stack." << std::endl;
    }

    void pop() {
        if (isEmpty()) {
            std::cerr << "Stack underflow. Cannot pop element from an empty stack." << std::endl;
            return;
        }

        std::cout << "Popped " << arr[top--] << " from the stack." << std::endl;
    }

    int peek() const {
        if (isEmpty()) {
            std::cerr << "Cannot peek into an empty stack." << std::endl;
            return -1;
        }

        return arr[top];
    }

    void display() const {
        if (isEmpty()) {
            std::cout << "Stack is empty." << std::endl;
            return;
        }

        std::cout << "Stack elements: ";
        for (int i = 0; i <= top; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Stack myStack;

    int choice, value;

    do {
        std::cout << "\n1. Push";
        std::cout << "\n2. Pop";
        std::cout << "\n3. Peek";
        std::cout << "\n4. Display";
        std::cout << "\n0. Exit";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the value to push: ";
                std::cin >> value;
                myStack.push(value);
                break;

            case 2:
                myStack.pop();
                break;

            case 3:
                std::cout << "Top element: " << myStack.peek() << std::endl;
                break;

            case 4:
                myStack.display();
                break;

            case 0:
                std::cout << "Exiting program." << std::endl;
                break;

            default:
                std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }

    } while (choice != 0);

    return 0;
}
