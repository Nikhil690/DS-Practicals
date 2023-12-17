#include <iostream>
#include <algorithm>

struct TreeNode {
    int data;
    int height;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : data(value), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    TreeNode* root;

    int getHeight(TreeNode* node) const {
        return (node == nullptr) ? 0 : node->height;
    }

    int getBalanceFactor(TreeNode* node) const {
        return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    TreeNode* rotateRight(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    TreeNode* rotateLeft(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    TreeNode* insertRecursive(TreeNode* node, int value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }

        if (value < node->data) {
            node->left = insertRecursive(node->left, value);
        } else if (value > node->data) {
            node->right = insertRecursive(node->right, value);
        } else {
            // Duplicate values are not allowed
            return node;
        }

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        int balance = getBalanceFactor(node);

        // Left-Left case
        if (balance > 1 && value < node->left->data) {
            return rotateRight(node);
        }
        // Right-Right case
        if (balance < -1 && value > node->right->data) {
            return rotateLeft(node);
        }
        // Left-Right case
        if (balance > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // Right-Left case
        if (balance < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    TreeNode* findMinNode(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    TreeNode* deleteRecursive(TreeNode* node, int value) {
        if (node == nullptr) {
            return node;
        }

        if (value < node->data) {
            node->left = deleteRecursive(node->left, value);
        } else if (value > node->data) {
            node->right = deleteRecursive(node->right, value);
        } else {
            if ((node->left == nullptr) || (node->right == nullptr)) {
                TreeNode* temp = (node->left != nullptr) ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                TreeNode* temp = findMinNode(node->right);
                node->data = temp->data;
                node->right = deleteRecursive(node->right, temp->data);
            }
        }

        if (node == nullptr) {
            return node;
        }

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        int balance = getBalanceFactor(node);

        // Left-Left case
        if (balance > 1 && getBalanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }
        // Left-Right case
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // Right-Right case
        if (balance < -1 && getBalanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }
        // Right-Left case
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    TreeNode* search(TreeNode* node, int value) const {
        if (node == nullptr || node->data == value) {
            return node;
        }

        if (value < node->data) {
            return search(node->left, value);
        }

        return search(node->right, value);
    }

    void displayInorder(TreeNode* node) const {
        if (node == nullptr) {
            return;
        }

        displayInorder(node->left);
        std::cout << node->data << " ";
        displayInorder(node->right);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int value) {
        root = insertRecursive(root, value);
    }

    void remove(int value) {
        root = deleteRecursive(root, value);
    }

    bool search(int value) const {
        return search(root, value) != nullptr;
    }

    void displayInorder() const {
        std::cout << "Inorder Traversal: ";
        displayInorder(root);
        std::cout << std::endl;
    }
};

int main() {
    AVLTree avl;

    int choice, value;

    do {
        std::cout << "\n1. Insert";
        std::cout << "\n2. Remove";
        std::cout << "\n3. Search";
        std::cout << "\n4. Display Inorder";
        std::cout << "\n0. Exit";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the value to insert: ";
                std::cin >> value;
                avl.insert(value);
                break;

            case 2:
                std::cout << "Enter the value to remove: ";
                std::cin >> value;
                avl.remove(value);
                break;

            case 3:
                std::cout << "Enter the value to search: ";
                std::cin >> value;
                if (avl.search(value)) {
                    std::cout << value << " is present in the AVL tree." << std::endl;
                } else {
                    std::cout << value << " is not present in the AVL tree." << std::endl;
                }
                break;

            case 4:
                avl.displayInorder();
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
