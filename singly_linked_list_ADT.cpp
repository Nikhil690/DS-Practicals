#include <iostream>

// Node structure to represent each element in the linked list
template <typename T>
struct Node {
    T data;
    Node* next;

    // Constructor
    Node(T value) : data(value), next(nullptr) {}
};

// SinglyLinkedList class
template <typename T>
class SinglyLinkedList {
private:
    Node<T>* head;

public:
    // Constructor
    SinglyLinkedList() : head(nullptr) {}

    // Function to insert an element at the beginning of the list
    void insertAtBeginning(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
    }

    // Function to insert an element at position i in the list
    void insertAtPosition(int i, T value) {
        if (i <= 0) {
            std::cerr << "Invalid position" << std::endl;
            return;
        }

        Node<T>* newNode = new Node<T>(value);

        if (i == 1) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node<T>* current = head;
        for (int pos = 1; pos < i - 1 && current != nullptr; ++pos) {
            current = current->next;
        }

        if (current == nullptr) {
            std::cerr << "Invalid position" << std::endl;
            delete newNode;
            return;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    // Function to remove an element from the beginning of the list
    void removeFromBeginning() {
        if (head == nullptr) {
            std::cerr << "List is empty" << std::endl;
            return;
        }

        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }

    // Function to remove an element from position i in the list
    void removeFromPosition(int i) {
        if (i <= 0 || head == nullptr) {
            std::cerr << "Invalid position or list is empty" << std::endl;
            return;
        }

        if (i == 1) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node<T>* current = head;
        for (int pos = 1; pos < i - 1 && current != nullptr; ++pos) {
            current = current->next;
        }

        if (current == nullptr || current->next == nullptr) {
            std::cerr << "Invalid position" << std::endl;
            return;
        }

        Node<T>* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }

    // Function to search for an element and return its pointer
    Node<T>* searchElement(T value) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
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
    SinglyLinkedList<int> myList;

    int choice;
    do {
        std::cout << "\n1. Insert at the beginning\n"
                     "2. Insert at a specific position\n"
                     "3. Remove from the beginning\n"
                     "4. Remove from a specific position\n"
                     "5. Search for an element\n"
                     "6. Display the list\n"
                     "0. Exit\n"
                     "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int value;
                std::cout << "Enter the value to insert: ";
                std::cin >> value;
                myList.insertAtBeginning(value);
                break;
            }
            case 2: {
                int position, value;
                std::cout << "Enter the position to insert: ";
                std::cin >> position;
                std::cout << "Enter the value to insert: ";
                std::cin >> value;
                myList.insertAtPosition(position, value);
                break;
            }
            case 3:
                myList.removeFromBeginning();
                break;
            case 4: {
                int position;
                std::cout << "Enter the position to remove: ";
                std::cin >> position;
                myList.removeFromPosition(position);
                break;
            }
            case 5: {
                int value;
                std::cout << "Enter the value to search: ";
                std::cin >> value;
                Node<int>* result = myList.searchElement(value);
                if (result != nullptr) {
                    std::cout << "Element " << value << " found at address: " << result << std::endl;
                } else {
                    std::cout << "Element " << value << " not found in the list." << std::endl;
                }
                break;
            }
            case 6:
                std::cout << "Linked List: ";
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
