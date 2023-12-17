#include <iostream>

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void insertAtFront(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    void removeFromFront() {
        if (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    int getFront() const {
        return (head != nullptr) ? head->data : -1; // Return a default value or throw an exception based on your requirements
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void display() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

class Stack {
private:
    LinkedList list;

public:
    void push(int value) {
        list.insertAtFront(value);
        std::cout << "Pushed " << value << " onto the stack." << std::endl;
    }

    void pop() {
        if (!list.isEmpty()) {
            list.removeFromFront();
            std::cout << "Popped from the stack." << std::endl;
        } else {
            std::cerr << "Stack underflow. Cannot pop from an empty stack." << std::endl;
        }
    }

    int peek() const {
        int topValue = list.getFront();
        if (topValue != -1) {
            std::cout << "Top element: " << topValue << std::endl;
        } else {
            std::cerr << "Cannot peek into an empty stack." << std::endl;
        }
        return topValue;
    }

    void display() const {
        list.display();
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
                myStack.peek();
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
