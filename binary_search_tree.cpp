#include <iostream>

template <typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(T value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;

    TreeNode<T>* insert(TreeNode<T>* node, T value) {
        if (!node) return new TreeNode<T>(value);
        if (value < node->data) node->left = insert(node->left, value);
        else if (value > node->data) node->right = insert(node->right, value);
        return node;
    }

    TreeNode<T>* findMin(TreeNode<T>* node) {
        while (node->left) node = node->left;
        return node;
    }

    TreeNode<T>* deleteNode(TreeNode<T>* node, T value) {
        if (!node) return nullptr;
        if (value < node->data) node->left = deleteNode(node->left, value);
        else if (value > node->data) node->right = deleteNode(node->right, value);
        else {
            if (!node->left) {
                TreeNode<T>* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                TreeNode<T>* temp = node->left;
                delete node;
                return temp;
            }
            TreeNode<T>* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    TreeNode<T>* search(TreeNode<T>* node, T value) {
        if (!node || node->data == value) return node;
        return (value < node->data) ? search(node->left, value) : search(node->right, value);
    }

    void inorderTraversal(TreeNode<T>* node) const {
        if (node) {
            inorderTraversal(node->left);
            std::cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert() {
        T value;
        std::cout << "Enter the value to insert: ";
        std::cin >> value;
        root = insert(root, value);
    }

    void deleteNode() {
        T value;
        std::cout << "Enter the value to delete: ";
        std::cin >> value;
        root = deleteNode(root, value);
    }

    void search() {
        T value;
        std::cout << "Enter the value to search: ";
        std::cin >> value;
        TreeNode<T>* foundNode = search(root, value);
        if (foundNode) std::cout << "Element " << value << " found in the BST." << std::endl;
        else std::cout << "Element " << value << " not found in the BST." << std::endl;
    }

    void displayInorder() const {
        std::cout << "Inorder: ";
        inorderTraversal(root);
        std::cout << std::endl;
    }
};

int main() {
    BinarySearchTree<int> myBST;
    int choice;

    do {
        std::cout << "\n1. Insert an element\n"
                     "2. Delete an element\n"
                     "3. Search for an element\n"
                     "4. Display the tree (Inorder)\n"
                     "0. Exit\n"
                     "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                myBST.insert();
                break;
            case 2:
                myBST.deleteNode();
                break;
            case 3:
                myBST.search();
                break;
            case 4:
                myBST.displayInorder();
                break;
            case 0:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
