#include <iostream>

class CircularQueue {
private:
    static const int MAX_SIZE = 5; // Adjust the maximum size as needed
    int* arr;
    int front;
    int rear;

public:
    CircularQueue() : front(-1), rear(-1) {
        arr = new int[MAX_SIZE];
    }

    ~CircularQueue() {
        delete[] arr;
    }

    bool isEmpty() const {
        return front == -1 && rear == -1;
    }

    bool isFull() const {
        return (rear + 1) % MAX_SIZE == front;
    }

    void enqueue(int value) {
        if (isFull()) {
            std::cerr << "Queue overflow. Cannot enqueue element." << std::endl;
            return;
        }

        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % MAX_SIZE;
        }

        arr[rear] = value;
        std::cout << "Enqueued " << value << " into the queue." << std::endl;
    }

    void dequeue() {
        if (isEmpty()) {
            std::cerr << "Queue underflow. Cannot dequeue from an empty queue." << std::endl;
            return;
        }

        std::cout << "Dequeued " << arr[front] << " from the queue." << std::endl;

        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % MAX_SIZE;
        }
    }

    int peek() const {
        if (isEmpty()) {
            std::cerr << "Cannot peek into an empty queue." << std::endl;
            return -1; // Return a default value or throw an exception based on your requirements
        }

        return arr[front];
    }

    void display() const {
        if (isEmpty()) {
            std::cout << "Queue is empty." << std::endl;
            return;
        }

        int current = front;
        std::cout << "Queue elements: ";
        do {
            std::cout << arr[current] << " ";
            current = (current + 1) % MAX_SIZE;
        } while (current != (rear + 1) % MAX_SIZE);

        std::cout << std::endl;
    }
};

int main() {
    CircularQueue myQueue;

    int choice, value;

    do {
        std::cout << "\n1. Enqueue";
        std::cout << "\n2. Dequeue";
        std::cout << "\n3. Peek";
        std::cout << "\n4. Display";
        std::cout << "\n0. Exit";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the value to enqueue: ";
                std::cin >> value;
                myQueue.enqueue(value);
                break;

            case 2:
                myQueue.dequeue();
                break;

            case 3:
                std::cout << "Front element: " << myQueue.peek() << std::endl;
                break;

            case 4:
                myQueue.display();
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
