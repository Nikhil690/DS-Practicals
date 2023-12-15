#include <iostream>
#include <algorithm>

// Node structure to represent each element in the AVL tree
template <typename T>
struct AVLNode {
    T data;
    AVLNode* left;
    AVLNode* right;
    int height; // Height of the node

    // Constructor
    AVLNode(T value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

// AVLTree class
template <typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    // Function to get the height of a node
    int getHeight(AVLNode<T>* node) {
        return (node == nullptr) ? 0 : node->height;
    }

    // Function to update the height of a node
    void updateHeight(AVLNode<T>* node) {
        if (node != nullptr) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    // Function to perform a right rotation
    AVLNode<T>* rightRotate(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        updateHeight(y);
        updateHeight(x);

        // Return new root
        return x;
    }

    // Function to perform a left rotation
    AVLNode<T>* leftRotate(AVLNode<T>* x) {
        AVLNode<T>* y = x->right;
        AVLNode<T>* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        updateHeight(x);
        updateHeight(y);

        // Return new root
        return y;
    }

    // Function to get the balance factor of a node
    int getBalanceFactor(AVLNode<T>* node) {
        return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    // Function to insert a value into the AVL tree
    AVLNode<T>* insert(AVLNode<T>* node, T value) {
        // Perform standard BST insert
        if (node == nullptr) {
            return new AVLNode<T>(value);
        }

        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        } else {
            // Duplicate values are not allowed in this example
            return node;
        }

        // Update height of the current node
        updateHeight(node);

        // Get the balance factor to check if this node became unbalanced
        int balance = getBalanceFactor(node);

        // Left Left Case
        if (balance > 1 && value < node->left->data) {
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && value > node->right->data) {
            return leftRotate(node);
        }

        // Left Right Case
        if (balance > 1 && value > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && value < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // No rotation needed, return the unchanged node
        return node;
    }

    // Function to search for a value in the AVL tree
    AVLNode<T>* search(AVLNode<T>* node, T value) {
        if (node == nullptr || node->data == value) {
            return node;
        }

        if (value < node->data) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }

public:
    // Constructor
    AVLTree() : root(nullptr) {}

    // Function to insert a value into the AVL tree
    void insert(T value) {
        root = insert(root, value);
    }

    // Function to search for a value in the AVL tree
    AVLNode<T>* search(T value) {
        return search(root, value);
    }
};

int main() {
    // Example usage of the AVLTree
    AVLTree<int> myAVL;

    int choice;
    do {
        std::cout << "\n1. Insert an element\n"
                     "2. Search for an element\n"
                     "0. Exit\n"
                     "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int value;
                std::cout << "Enter the value to insert: ";
                std::cin >> value;
                myAVL.insert(value);
                break;
            }
            case 2: {
                int value;
                std::cout << "Enter the value to search: ";
                std::cin >> value;
                AVLNode<int>* foundNode = myAVL.search(value);
                if (foundNode != nullptr) {
                    std::cout << "Element " << value << " found in the AVL tree." << std::endl;
                } else {
                    std::cout << "Element " << value << " not found in the AVL tree." << std::endl;
                }
                break;
            }
            case 0:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
