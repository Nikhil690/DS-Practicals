#include <iostream>

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class CircularLinkedList {
private:
    Node* head;

public:
    CircularLinkedList() : head(nullptr) {}

    // (i) Insert an element x at the front of the circularly linked list
    void insertAtFront(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            head->next = head; // Point to itself in a circular list
        } else {
            newNode->next = head;
            Node* current = head;
            while (current->next != head) {
                current = current->next;
            }
            current->next = newNode;
            head = newNode;
        }
    }

    // (ii) Insert an element x after an element y in the circularly linked list
    void insertAfterElement(int valueToInsert, int valueAfter) {
        if (head == nullptr) {
            std::cerr << "List is empty. Cannot insert after element." << std::endl;
            return;
        }

        Node* newNode = new Node(valueToInsert);
        Node* current = head;

        do {
            if (current->data == valueAfter) {
                newNode->next = current->next;
                current->next = newNode;
                return;
            }
            current = current->next;
        } while (current != head);

        std::cerr << "Element " << valueAfter << " not found in the list." << std::endl;
    }

    // (iii) Insert an element x at the back of the circularly linked list
    void insertAtBack(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            head->next = head; // Point to itself in a circular list
        } else {
            Node* current = head;
            while (current->next != head) {
                current = current->next;
            }
            current->next = newNode;
            newNode->next = head;
        }
    }

    // (iv) Remove an element from the back of the circularly linked list
    void removeFromBack() {
        if (head == nullptr) {
            std::cerr << "List is empty. Cannot remove from the back." << std::endl;
            return;
        }

        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }

        Node* current = head;
        Node* previous = nullptr;
        while (current->next != head) {
            previous = current;
            current = current->next;
        }

        previous->next = head;
        delete current;
    }

    // (v) Remove an element from the front of the circularly linked list
    void removeFromFront() {
        if (head == nullptr) {
            std::cerr << "List is empty. Cannot remove from the front." << std::endl;
            return;
        }

        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }

        Node* current = head;
        while (current->next != head) {
            current = current->next;
        }

        Node* temp = head;
        current->next = head->next;
        head = head->next;
        delete temp;
    }

    // (vi) Remove the element x from the circularly linked list
    void removeElement(int valueToRemove) {
        if (head == nullptr) {
            std::cerr << "List is empty. Cannot remove element." << std::endl;
            return;
        }

        if (head->data == valueToRemove) {
            removeFromFront();
            return;
        }

        Node* current = head;
        Node* previous = nullptr;

        do {
            if (current->data == valueToRemove) {
                previous->next = current->next;
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        } while (current != head);

        std::cerr << "Element " << valueToRemove << " not found in the list." << std::endl;
    }

    // (vii) Search for an element x in the circularly linked list and return its pointer
    Node* searchElement(int value) const {
        if (head == nullptr) {
            return nullptr;
        }

        Node* current = head;

        do {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        } while (current != head);

        return nullptr;
    }

    // (viii) Concatenate two circularly linked lists
    void concatenate(CircularLinkedList& otherList) {
        if (head == nullptr) {
            head = otherList.head;
        } else if (otherList.head != nullptr) {
            Node* current = head;
            while (current->next != head) {
                current = current->next;
            }
            current->next = otherList.head;
            otherList.head = head;
        }

        // Make the other list empty after concatenation
        otherList.head = nullptr;
    }

    // Function to display the circularly linked list
    void display() const {
        if (head == nullptr) {
            std::cout << "List is empty." << std::endl;
            return;
        }

        Node* current = head;

        do {
            std::cout << current->data << " ";
            current = current->next;
        } while (current != head);

        std::cout << std::endl;
    }
};

// Function to display the list
void displayList(const CircularLinkedList& list) {
    list.display();
}

int main() {
    CircularLinkedList myCircularList;

    int choice, value, valueAfter;
    Node* result = nullptr;

    do {
        std::cout << "\n1. Insert at the front";
        std::cout << "\n2. Insert after an element";
        std::cout << "\n3. Insert at the back";
        std::cout << "\n4. Remove from the back";
        std::cout << "\n5. Remove from the front";
        std::cout << "\n6. Remove an element";
        std::cout << "\n7. Search for an element";
        std::cout << "\n8. Concatenate with another list";
        std::cout << "\n0. Exit";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the value to insert at the front: ";
                std::cin >> value;
                myCircularList.insertAtFront(value);
                break;

            case 2:
                std::cout << "Enter the value to insert: ";
                std::cin >> value;
                std::cout << "Enter the value after which to insert: ";
                std::cin >> valueAfter;
                myCircularList.insertAfterElement(value, valueAfter);
                break;

            case 3:
                std::cout << "Enter the value to insert at the back: ";
                std::cin >> value;
                myCircularList.insertAtBack(value);
                break;

            case 4:
                myCircularList.removeFromBack();
                break;

            case 5:
                myCircularList.removeFromFront();
                break;

            case 6:
                std::cout << "Enter the value to remove: ";
                std::cin >> value;
                myCircularList.removeElement(value);
                break;

            case 7:
                std::cout << "Enter the value to search: ";
                std::cin >> value;
                result = myCircularList.searchElement(value);
                if (result != nullptr) {
                    std::cout << "Element " << value << " found at address: " << result << std::endl;
                } else {
                    std::cout << "Element " << value << " not found in the list." << std::endl;
                }
                break;

            case 8: {
                CircularLinkedList anotherCircularList;
                std::cout << "Enter elements for the second list (enter -1 to stop): ";
                while (true) {
                    std::cin >> value;
                    if (value == -1) {
                        break;
                    }
                    anotherCircularList.insertAtBack(value);
                }
                myCircularList.concatenate(anotherCircularList);
                std::cout << "Lists concatenated." << std::endl;
                break;
            }

            case 0:
                std::cout << "Exiting program." << std::endl;
                break;

            default:
                std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }

        std::cout << "Linked List: ", displayList(myCircularList);

    } while (choice != 0);

    return 0;
}

