#include <iostream>

// Node structure to represent each element in the circular linked list
template <typename T>
struct Node {
    T data;
    Node* next;

    // Constructor
    Node(T value) : data(value), next(nullptr) {}
};

// CircularLinkedList class as an ADT
template <typename T>
class CircularLinkedList {
private:
    Node<T>* head;

public:
    // Constructor
    CircularLinkedList() : head(nullptr) {}

    // Destructor to free memory when the object is destroyed
    ~CircularLinkedList() {
        if (head == nullptr) {
            return;
        }

        Node<T>* current = head->next;
        while (current != head) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }

        delete head;
    }

    // Function to insert an element in the list
    void insertElement(T value) {
        Node<T>* newNode = new Node<T>(value);

        if (head == nullptr) {
            head = newNode;
            newNode->next = head;
        } else {
            Node<T>* last = head;
            while (last->next != head) {
                last = last->next;
            }

            last->next = newNode;
            newNode->next = head;
        }
    }

    // Function to remove an element from the list
    void removeElement(T value) {
        if (head == nullptr) {
            std::cerr << "List is empty" << std::endl;
            return;
        }

        Node<T>* current = head;
        Node<T>* prev = nullptr;

        do {
            if (current->data == value) {
                if (current == head) {
                    if (current->next == head) {
                        // Only one element in the list
                        delete head;
                        head = nullptr;
                    } else {
                        Node<T>* last = head;
                        while (last->next != head) {
                            last = last->next;
                        }

                        last->next = head->next;
                        Node<T>* temp = head;
                        head = head->next;
                        delete temp;
                    }
                } else {
                    prev->next = current->next;
                    delete current;
                }
                return;
            }

            prev = current;
            current = current->next;

        } while (current != head);

        std::cerr << "Element not found in the list" << std::endl;
    }

    // Function to search for an element and return its pointer
    Node<T>* searchElement(T value) {
        if (head == nullptr) {
            return nullptr;
        }

        Node<T>* current = head;
        do {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        } while (current != head);

        return nullptr;
    }

    // Function to display the elements in the list
    void display() {
        if (head == nullptr) {
            std::cout << "List is empty" << std::endl;
            return;
        }

        Node<T>* current = head;
        do {
            std::cout << current->data << " ";
            current = current->next;
        } while (current != head);
        std::cout << std::endl;
    }
};

int main() {
    CircularLinkedList<int> myList;

    int choice;
    do {
        std::cout << "\n1. Insert an element\n"
                     "2. Remove an element\n"
                     "3. Search for an element\n"
                     "4. Display the list\n"
                     "0. Exit\n"
                     "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int value;
                std::cout << "Enter the value to insert: ";
                std::cin >> value;
                myList.insertElement(value);
                break;
            }
            case 2: {
                int value;
                std::cout << "Enter the value to remove: ";
                std::cin >> value;
                myList.removeElement(value);
                break;
            }
            case 3: {
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
            case 4:
                std::cout << "Circular Linked List: ";
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
