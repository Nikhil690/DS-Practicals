#include <iostream>
#include <queue>

// Queue class as an ADT
template <typename T>
class Queue {
private:
    std::queue<T> data;

public:
    // Function to enqueue (push) an element into the queue
    void enqueue(T value) {
        data.push(value);
    }

    // Function to dequeue (pop) an element from the queue
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        T front = data.front();
        data.pop();
        return front;
    }

    // Function to check if the queue is empty
    bool isEmpty() const {
        return data.empty();
    }

    // Function to get the front element of the queue without dequeuing it
    T front() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        return data.front();
    }

    // Function to get the size of the queue
    size_t size() const {
        return data.size();
    }
};

int main() {
    // Example usage of the Queue ADT
    Queue<int> myQueue;

    int numElements;
    std::cout << "Enter the number of elements to enqueue: ";
    std::cin >> numElements;

    // Enqueue elements based on user input
    for (int i = 0; i < numElements; ++i) {
        int value;
        std::cout << "Enter element #" << i + 1 << ": ";
        std::cin >> value;
        myQueue.enqueue(value);
    }

    // Display the front element
    if (!myQueue.isEmpty()) {
        std::cout << "Front element: " << myQueue.front() << std::endl;
    }

    // Dequeue elements
    while (!myQueue.isEmpty()) {
        // std::cout << "Dequeued: " << myQueue.dequeue() << std::endl;  //uncomment this if you want to dequeue the elements
    }

    // Try to dequeue from an empty queue (will throw an exception)
    try {
        myQueue.dequeue();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
