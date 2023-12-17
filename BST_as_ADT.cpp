#include <iostream>
#include <queue>

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    TreeNode* root;

    TreeNode* insertRecursive(TreeNode* current, int value) {
        if (current == nullptr) {
            return new TreeNode(value);
        }

        if (value < current->data) {
            current->left = insertRecursive(current->left, value);
        } else if (value > current->data) {
            current->right = insertRecursive(current->right, value);
        }

        return current;
    }

    TreeNode* findMinNode(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    TreeNode* deleteRecursive(TreeNode* current, int value) {
        if (current == nullptr) {
            return nullptr;
        }

        if (value < current->data) {
            current->left = deleteRecursive(current->left, value);
        } else if (value > current->data) {
            current->right = deleteRecursive(current->right, value);
        } else {
            if (current->left == nullptr) {
                TreeNode* temp = current->right;
                delete current;
                return temp;
            } else if (current->right == nullptr) {
                TreeNode* temp = current->left;
                delete current;
                return temp;
            }

            TreeNode* temp = findMinNode(current->right);
            current->data = temp->data;
            current->right = deleteRecursive(current->right, temp->data);
        }

        return current;
    }

    TreeNode* searchAndChange(TreeNode* current, int oldValue, int newValue) {
        if (current == nullptr) {
            return nullptr;
        }

        if (oldValue < current->data) {
            current->left = searchAndChange(current->left, oldValue, newValue);
        } else if (oldValue > current->data) {
            current->right = searchAndChange(current->right, oldValue, newValue);
        } else {
            current->data = newValue;
        }

        return current;
    }

    void levelOrderTraversal(TreeNode* node) const {
        if (node == nullptr) {
            return;
        }

        std::queue<TreeNode*> q;
        q.push(node);

        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();

            std::cout << current->data << " ";

            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
    }

    int calculateHeight(TreeNode* node) const {
        if (node == nullptr) {
            return 0;
        }

        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);

        return std::max(leftHeight, rightHeight) + 1;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int value) {
        root = insertRecursive(root, value);
    }

    void remove(int value) {
        root = deleteRecursive(root, value);
    }

    void searchAndChangeValue(int oldValue, int newValue) {
        root = searchAndChange(root, oldValue, newValue);
    }

    void displayPreorder() const {
        std::cout << "Preorder Traversal: ";
        displayPreorder(root);
        std::cout << std::endl;
    }

    void displayInorder() const {
        std::cout << "Inorder Traversal: ";
        displayInorder(root);
        std::cout << std::endl;
    }

    void displayPostorder() const {
        std::cout << "Postorder Traversal: ";
        displayPostorder(root);
        std::cout << std::endl;
    }

    void displayLevelOrder() const {
        std::cout << "Level-order Traversal: ";
        levelOrderTraversal(root);
        std::cout << std::endl;
    }

    void displayHeight() const {
        int height = calculateHeight(root);
        std::cout << "Height of the BST: " << height << std::endl;
    }

private:
    void displayPreorder(TreeNode* node) const {
        if (node == nullptr) {
            return;
        }

        std::cout << node->data << " ";
        displayPreorder(node->left);
        displayPreorder(node->right);
    }

    void displayInorder(TreeNode* node) const {
        if (node == nullptr) {
            return;
        }

        displayInorder(node->left);
        std::cout << node->data << " ";
        displayInorder(node->right);
    }

    void displayPostorder(TreeNode* node) const {
        if (node == nullptr) {
            return;
        }

        displayPostorder(node->left);
        displayPostorder(node->right);
        std::cout << node->data << " ";
    }
};

int main() {
    BinarySearchTree bst;

    int choice, value, oldValue, newValue;

    do {
        std::cout << "\n1. Insert";
        std::cout << "\n2. Remove";
        std::cout << "\n3. Search and Change Value";
        std::cout << "\n4. Display Preorder";
        std::cout << "\n5. Display Inorder";
        std::cout << "\n6. Display Postorder";
        std::cout << "\n7. Display Level Order";
        std::cout << "\n8. Display Height";
        std::cout << "\n0. Exit";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the value to insert: ";
                std::cin >> value;
                bst.insert(value);
                break;

            case 2:
                std::cout << "Enter the value to remove: ";
                std::cin >> value;
                bst.remove(value);
                break;

            case 3:
                std::cout << "Enter the value to search and change: ";
                std::cin >> oldValue;
                std::cout << "Enter the new value: ";
                std::cin >> newValue;
                bst.searchAndChangeValue(oldValue, newValue);
                break;

            case 4:
                bst.displayPreorder();
                break;

            case 5:
                bst.displayInorder();
                break;

            case 6:
                bst.displayPostorder();
                break;

            case 7:
                bst.displayLevelOrder();
                break;

            case 8:
                bst.displayHeight();
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
