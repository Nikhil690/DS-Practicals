#include <iostream>

struct Node
{
    int data;
    Node *prev;
    Node *next;

    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList
{
private:
    Node *head;

public:
    DoublyLinkedList() : head(nullptr) {}

    // (i) Insert an element x at the beginning of the doubly linked list
    void insertAtBeginning(int value)
    {
        Node *newNode = new Node(value);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // (ii) Insert an element x at ith position in the doubly linked list
    void insertAtPosition(int value, int position)
    {
        Node *newNode = new Node(value);
        if (position <= 0)
        {
            std::cerr << "Invalid position for insertion." << std::endl;
            return;
        }

        if (head == nullptr && position > 1)
        {
            std::cerr << "Invalid position for insertion. List is empty." << std::endl;
            return;
        }

        if (position == 1)
        {
            newNode->next = head;
            if (head != nullptr)
            {
                head->prev = newNode;
            }
            head = newNode;
            return;
        }

        Node *current = head;
        for (int i = 1; i < position - 1 && current != nullptr; ++i)
        {
            current = current->next;
        }

        if (current == nullptr)
        {
            std::cerr << "Invalid position for insertion." << std::endl;
            return;
        }

        newNode->next = current->next;
        newNode->prev = current;
        if (current->next != nullptr)
        {
            current->next->prev = newNode;
        }
        current->next = newNode;
    }

    // (iii) Insert an element x at the end of the doubly linked list
    void insertAtEnd(int value)
    {
        Node *newNode = new Node(value);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
            newNode->prev = current;
        }
    }

    // (iv) Remove an element from the beginning of the doubly linked list
    void removeFromBeginning()
    {
        if (head == nullptr)
        {
            std::cerr << "List is empty. Cannot remove from the beginning." << std::endl;
            return;
        }

        Node *temp = head;
        head = head->next;
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        delete temp;
    }

    // (v) Remove an element from ith position in the doubly linked list
    void removeFromPosition(int position)
    {
        if (head == nullptr)
        {
            std::cerr << "List is empty. Cannot remove from position." << std::endl;
            return;
        }

        if (position <= 0)
        {
            std::cerr << "Invalid position for removal." << std::endl;
            return;
        }

        Node *current = head;
        for (int i = 1; i < position && current != nullptr; ++i)
        {
            current = current->next;
        }

        if (current == nullptr)
        {
            std::cerr << "Invalid position for removal." << std::endl;
            return;
        }

        if (current->prev != nullptr)
        {
            current->prev->next = current->next;
        }
        else
        {
            head = current->next;
        }

        if (current->next != nullptr)
        {
            current->next->prev = current->prev;
        }

        delete current;
    }

    // (vi) Remove an element from the end of the doubly linked list
    void removeFromEnd()
    {
        if (head == nullptr)
        {
            std::cerr << "List is empty. Cannot remove from the end." << std::endl;
            return;
        }

        Node *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }

        if (current->prev != nullptr)
        {
            current->prev->next = nullptr;
        }
        else
        {
            head = nullptr;
        }

        delete current;
    }

    // (vii) Search for an element x in the doubly linked list and return its pointer
    Node *searchElement(int value) const
    {
        Node *current = head;
        while (current != nullptr)
        {
            if (current->data == value)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // (viii) Concatenate two doubly linked lists
    void concatenate(DoublyLinkedList &otherList)
    {
        if (head == nullptr)
        {
            head = otherList.head;
        }
        else if (otherList.head != nullptr)
        {
            Node *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = otherList.head;
            otherList.head->prev = current;
        }

        otherList.head = nullptr;
    }

    // Function to display the doubly linked list in both directions
    void display() const
    {
        Node *currentForward = head;
        Node *currentBackward = nullptr;

        // Forward display
        std::cout << "Forward: ";
        while (currentForward != nullptr)
        {
            std::cout << currentForward->data << " ";
            currentBackward = currentForward; // Set currentBackward to the current node for backward traversal
            currentForward = currentForward->next;
        }

        // Backward display
        std::cout << "\nBackward: ";
        while (currentBackward != nullptr)
        {
            std::cout << currentBackward->data << " ";
            currentBackward = currentBackward->prev;
        }

        std::cout << std::endl;
    }
};

// Function to display the list
void displayList(const DoublyLinkedList &list)
{
    list.display();
}

int main()
{
    DoublyLinkedList myList;

    int choice, value, position;
    Node *result = nullptr;

    do
    {
        std::cout << "\n1. Insert at the beginning";
        std::cout << "\n2. Insert at a position";
        std::cout << "\n3. Insert at the end";
        std::cout << "\n4. Remove from the beginning";
        std::cout << "\n5. Remove from a position";
        std::cout << "\n6. Remove from the end";
        std::cout << "\n7. Search for an element by value";
        std::cout << "\n8. Concatenate with another list";
        std::cout << "\n0. Exit";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "Enter the value to insert: ";
            std::cin >> value;
            myList.insertAtBeginning(value);
            break;

        case 2:
            std::cout << "Enter the value to insert: ";
            std::cin >> value;
            std::cout << "Enter the position to insert: ";
            std::cin >> position;
            myList.insertAtPosition(value, position);
            break;

        case 3:
            std::cout << "Enter the value to insert at the end: ";
            std::cin >> value;
            myList.insertAtEnd(value);
            break;

        case 4:
            myList.removeFromBeginning();
            break;

        case 5:
            std::cout << "Enter the position to remove: ";
            std::cin >> position;
            myList.removeFromPosition(position);
            break;

        case 6:
            myList.removeFromEnd();
            break;

        case 7:
            std::cout << "Enter the value to search: ";
            std::cin >> value;
            result = myList.searchElement(value);
            if (result != nullptr)
            {
                std::cout << "Element " << value << " found at address: " << result << std::endl;
            }
            else
            {
                std::cout << "Element " << value << " not found in the list." << std::endl;
            }
            break;

        case 8:
        {
            DoublyLinkedList anotherList;
            std::cout << "Enter elements for the second list (enter -1 to stop): ";
            while (true)
            {
                std::cin >> value;
                if (value == -1)
                {
                    break;
                }
                anotherList.insertAtEnd(value);
            }
            myList.concatenate(anotherList);
            std::cout << "Lists concatenated." << std::endl;
            break;
        }

        case 0:
            std::cout << "Exiting program." << std::endl;
            break;

        default:
            std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }

        displayList(myList);

    } while (choice != 0);

    return 0;
}
