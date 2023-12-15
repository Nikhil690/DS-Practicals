#include <iostream>

template <typename T>
T getInput(const std::string& prompt) {
    T value;
    std::cout << prompt;
    std::cin >> value;
    return value;
}
template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class CircularLinkedList {
private:
    Node<T>* head;

public:
    CircularLinkedList() : head(nullptr) {}

    ~CircularLinkedList() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            if (head == temp) break; // Avoid infinite loop for a circular list with a single node
        }
    }

    void insertElement(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) head = newNode, newNode->next = head;
        else {
            Node<T>* last = head;
            while (last->next != head) last = last->next;
            last->next = newNode, newNode->next = head;
        }
    }

    void removeElement(T value) {
        if (!head) std::cerr << "List is empty\n";
        else {
            Node<T>* current = head, *prev = nullptr;
            do {
                if (current->data == value) {
                    if (current == head) {
                        if (current->next == head) head = nullptr;
                        else {
                            Node<T>* last = head;
                            while (last->next != head) last = last->next;
                            last->next = head->next, head = head->next;
                        }
                    } else prev->next = current->next;
                    delete current;
                    return;
                }
                prev = current, current = current->next;
            } while (current != head);
            std::cerr << "Element not found in the list\n";
        }
    }

    Node<T>* searchElement(T value) {
        if (!head) return nullptr;
        Node<T>* current = head;
        do {
            if (current->data == value) return current;
            current = current->next;
        } while (current != head);
        return nullptr;
    }

    void display() {
        if (!head) std::cout << "List is empty\n";
        else {
            Node<T>* current = head;
            do {
                std::cout << current->data << " ";
                current = current->next;
            } while (current != head);
            std::cout << std::endl;
        }
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
            case 1: myList.insertElement(getInput<int>("Enter the value to insert: ")); break;
            case 2: myList.removeElement(getInput<int>("Enter the value to remove: ")); break;
            case 3: {
                Node<int>* result = myList.searchElement(getInput<int>("Enter the value to search: "));
                if (result) std::cout << "Element found at address: " << result << std::endl;
                else std::cout << "Element not found in the list.\n";
                break;
            }
            case 4: std::cout << "Circular Linked List: "; myList.display(); break;
            case 0: std::cout << "Exiting program.\n"; break;
            default: std::cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
