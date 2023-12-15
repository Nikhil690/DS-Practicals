#include <iostream>

// Node structure to represent each element in the doubly linked list
template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    // Constructor
    Node(T value) : data(value), prev(nullptr), next(nullptr) {}
};

// DoublyLinkedList class as an ADT
template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    // Constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Destructor to free memory when the object is destroyed
    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Function to insert an element at the beginning of the list
    void insertAtBeginning(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Function to insert an element at the end of the list
    void insertAtEnd(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Function to remove an element from the beginning of the list
    void removeFromBeginning() {
        if (head == nullptr) {
            std::cerr << "List is empty" << std::endl;
            return;
        }

        Node<T>* temp = head;
        if (head == tail) {
            // Only one element in the list
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }

        delete temp;
    }

    // Function to remove an element from the end of the list
    void removeFromEnd() {
        if (tail == nullptr) {
            std::cerr << "List is empty" << std::endl;
            return;
        }

        Node<T>* temp = tail;
        if (head == tail) {
            // Only one element in the list
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }

        delete temp;
    }

    // Function to display the elements in the list
    void display() {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    // Example usage of the DoublyLinkedList ADT
    DoublyLinkedList<int> myList;

    int choice;
    do {
        std::cout << "\n1. Insert at the beginning\n"
                     "2. Insert at the end\n"
                     "3. Remove from the beginning\n"
                     "4. Remove from the end\n"
                     "5. Display the list\n"
                     "0. Exit\n"
                     "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int value;
                std::cout << "Enter the value to insert at the beginning: ";
                std::cin >> value;
                myList.insertAtBeginning(value);
                break;
            }
            case 2: {
                int value;
                std::cout << "Enter the value to insert at the end: ";
                std::cin >> value;
                myList.insertAtEnd(value);
                break;
            }
            case 3:
                myList.removeFromBeginning();
                break;
            case 4:
                myList.removeFromEnd();
                break;
            case 5:
                std::cout << "Doubly Linked List: ";
                myList.display();
                break;
            case 0:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
