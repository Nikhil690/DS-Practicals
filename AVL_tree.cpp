#include <iostream>
#include <algorithm>

template <typename T>
struct AVLNode {
    T data;
    AVLNode* left, *right;
    int height;

    AVLNode(T value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    int getHeight(AVLNode<T>* node) {
        return (node == nullptr) ? 0 : node->height;
    }

    void updateHeight(AVLNode<T>* node) {
        if (node) node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }

    AVLNode<T>* rightRotate(AVLNode<T>* y) {
        AVLNode<T>* x = y->left, *T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode<T>* leftRotate(AVLNode<T>* x) {
        AVLNode<T>* y = x->right, *T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    int getBalanceFactor(AVLNode<T>* node) {
        return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    AVLNode<T>* insert(AVLNode<T>* node, T value) {
        if (!node) return new AVLNode<T>(value);

        if (value < node->data) node->left = insert(node->left, value);
        else if (value > node->data) node->right = insert(node->right, value);
        else return node;

        updateHeight(node);
        int balance = getBalanceFactor(node);

        if (balance > 1 && value < node->left->data) return rightRotate(node);
        if (balance < -1 && value > node->right->data) return leftRotate(node);
        if (balance > 1 && value > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && value < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode<T>* search(AVLNode<T>* node, T value) {
        if (!node || node->data == value) return node;
        return (value < node->data) ? search(node->left, value) : search(node->right, value);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(T value) {
        root = insert(root, value);
    }

    AVLNode<T>* search(T value) {
        return search(root, value);
    }
};

int main() {
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
                if (foundNode) std::cout << "Element " << value << " found in the AVL tree." << std::endl;
                else std::cout << "Element " << value << " not found in the AVL tree." << std::endl;
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
