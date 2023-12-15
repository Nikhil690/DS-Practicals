#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class SinglyLinkedList {
private:
    Node<T>* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    void insertAtBeginning(T value) {
    Node<T>* newNode = new Node<T>(value);
    newNode->next = head;
    head = newNode;
    }


    void insertAtPosition(int i, T value) {
        if (i <= 0) { return; }
        Node<T>* newNode = new Node<T>(value);
        newNode->next = (i == 1) ? head : head->next;
        if (i != 1) {
            Node<T>* current = head;
            for (int pos = 1; pos < i - 1 && current != nullptr; ++pos) {
                current = current->next;
            }
            if (current != nullptr) { current->next = newNode; }
        }
        head = newNode;
    }

    void removeFromBeginning() {
        if (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void removeFromPosition(int i) {
        if (i <= 0 || head == nullptr) { return; }
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
        if (current != nullptr && current->next != nullptr) {
            Node<T>* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    Node<T>* searchElement(T value) {
        Node<T>* current = head;
        while (current != nullptr && current->data != value) {
            current = current->next;
        }
        return current;
    }

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
