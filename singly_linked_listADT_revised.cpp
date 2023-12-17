#include <iostream>

struct Node
{
    int data;
    Node *next;

    Node(int value) : data(value), next(nullptr) {}
};

class SinglyLinkedList
{
private:
    Node *head;

public:
    SinglyLinkedList() : head(nullptr) {}

    void insertAtBeginning(int value)
    {
        Node *newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    void insertAtPosition(int value, int position)
    {
        Node *newNode = new Node(value);

        if (position == 0)
        {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node *current = head;
        for (int i = 0; i < position - 1 && current != nullptr; ++i)
        {
            current = current->next;
        }

        if (current == nullptr)
        {
            std::cerr << "Invalid position for insertion." << std::endl;
            return;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    void removeFromBeginning()
    {
        if (head == nullptr)
        {
            std::cerr << "List is empty. Cannot remove from the beginning." << std::endl;
            return;
        }

        Node *temp = head;
        head = head->next;
        delete temp;
    }

    void removeFromPosition(int position)
    {
        if (head == nullptr)
        {
            std::cerr << "List is empty. Cannot remove from position." << std::endl;
            return;
        }

        if (position == 0)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node *current = head;
        for (int i = 0; i < position - 1 && current != nullptr; ++i)
        {
            current = current->next;
        }

        if (current == nullptr || current->next == nullptr)
        {
            std::cerr << "Invalid position for removal." << std::endl;
            return;
        }

        Node *temp = current->next;
        current->next = current->next->next;
        delete temp;
    }

    Node *searchElement(int value)
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

    void concatenate(SinglyLinkedList &otherList)
    {
        if (head == nullptr)
        {
            head = otherList.head;
        }
        else
        {
            Node *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = otherList.head;
        }

        otherList.head = nullptr;
    }

    void display() const
    {
        Node *current = head;
        while (current != nullptr)
        {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

// Function to display the list
void displayList(const SinglyLinkedList &list)
{
    std::cout << "Current List: ";
    list.display();
}

int main()
{
    SinglyLinkedList myList;

    int choice, value, position;
    Node *result = nullptr;

    do
    {
        std::cout << "\n1. Insert at the beginning";
        std::cout << "\n2. Insert at a position";
        std::cout << "\n3. Remove from the beginning";
        std::cout << "\n4. Remove from a position";
        std::cout << "\n5. Search for an element";
        std::cout << "\n6. Concatenate with another list";
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
            myList.removeFromBeginning();
            break;

        case 4:
            std::cout << "Enter the position to remove: ";
            std::cin >> position;
            myList.removeFromPosition(position);
            break;

        case 5:
            std::cout << "Enter the value to search: ";
            std::cin >> value;
            result = myList.searchElement(value); // Move the assignment outside the block
            if (result != nullptr)
            {
                std::cout << "Element " << value << " found at address: " << result << std::endl;
            }
            else
            {
                std::cout << "Element " << value << " not found in the list." << std::endl;
            }
            break;

        case 6:
        {
            SinglyLinkedList anotherList;
            std::cout << "Enter elements for the second list (enter -1 to stop): ";
            while (true)
            {
                std::cin >> value;
                if (value == -1)
                {
                    break;
                }
                anotherList.insertAtBeginning(value);
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
