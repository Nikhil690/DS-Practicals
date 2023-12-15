#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* prev, *next;
    Node(T value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head, *tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertAtBeginning(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) head = tail = newNode;
        else newNode->next = head, head->prev = newNode, head = newNode;
    }

    void insertAtEnd(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!tail) head = tail = newNode;
        else newNode->prev = tail, tail->next = newNode, tail = newNode;
    }

    void removeFromBeginning() {
        if (!head) std::cerr << "List is empty\n";
        else {
            Node<T>* temp = head;
            if (head == tail) head = tail = nullptr;
            else head = head->next, head->prev = nullptr;
            delete temp;
        }
    }

    void removeFromEnd() {
        if (!tail) std::cerr << "List is empty\n";
        else {
            Node<T>* temp = tail;
            if (head == tail) head = tail = nullptr;
            else tail = tail->prev, tail->next = nullptr;
            delete temp;
        }
    }

    void display() {
        Node<T>* current = head;
        while (current) std::cout << current->data << " ", current = current->next;
        std::cout << std::endl;
    }
};

int main() {
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
                std::cout << "Enter value to insert at the beginning: ";
                std::cin >> value;
                myList.insertAtBeginning(value);
                break;
            }
            case 2: {
                int value;
                std::cout << "Enter value to insert at the end: ";
                std::cin >> value;
                myList.insertAtEnd(value);
                break;
            }
            case 3: myList.removeFromBeginning(); break;
            case 4: myList.removeFromEnd(); break;
            case 5: std::cout << "Doubly Linked List: "; myList.display(); break;
            case 0: std::cout << "Exiting program.\n"; break;
            default: std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
