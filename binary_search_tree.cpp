#include <iostream>

// Node structure to represent each element in the BST
template <typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;

    // Constructor
    TreeNode(T value) : data(value), left(nullptr), right(nullptr) {}
};

// BinarySearchTree class as an ADT
template <typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;

    // Function to insert a value into the BST
    TreeNode<T>* insert(TreeNode<T>* node, T value) {
        if (node == nullptr) {
            return new TreeNode<T>(value);
        }

        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }

        return node;
    }

    // Function to find the minimum value node in a subtree
    TreeNode<T>* findMin(TreeNode<T>* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Function to delete a value from the BST
    TreeNode<T>* deleteNode(TreeNode<T>* node, T value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (value < node->data) {
            node->left = deleteNode(node->left, value);
        } else if (value > node->data) {
            node->right = deleteNode(node->right, value);
        } else {
            // Node with only one child or no child
            if (node->left == nullptr) {
                TreeNode<T>* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                TreeNode<T>* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: Get the inorder successor (smallest in the right subtree)
            TreeNode<T>* temp = findMin(node->right);

            // Copy the inorder successor's data to this node
            node->data = temp->data;

            // Delete the inorder successor
            node->right = deleteNode(node->right, temp->data);
        }

        return node;
    }

    // Function to search for a value in the BST
    TreeNode<T>* search(TreeNode<T>* node, T value) {
        if (node == nullptr || node->data == value) {
            return node;
        }

        if (value < node->data) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }

    // Function to perform preorder traversal
    void preorderTraversal(TreeNode<T>* node) const {
        if (node != nullptr) {
            std::cout << node->data << " ";
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }

    // Function to perform inorder traversal
    void inorderTraversal(TreeNode<T>* node) const {
        if (node != nullptr) {
            inorderTraversal(node->left);
            std::cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }

    // Function to perform postorder traversal
    void postorderTraversal(TreeNode<T>* node) const {
        if (node != nullptr) {
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            std::cout << node->data << " ";
        }
    }

public:
    // Constructor
    BinarySearchTree() : root(nullptr) {}

    // Function to insert a value into the BST
    void insert(T value) {
        root = insert(root, value);
    }

    // Function to delete a value from the BST
    void deleteNode(T value) {
        root = deleteNode(root, value);
    }

    // Function to search for a value in the BST
    TreeNode<T>* search(T value) {
        return search(root, value);
    }

    // Function to display elements in preorder traversal
    void displayPreorder() const {
        std::cout << "Preorder: ";
        preorderTraversal(root);
        std::cout << std::endl;
    }

    // Function to display elements in inorder traversal
    void displayInorder() const {
        std::cout << "Inorder: ";
        inorderTraversal(root);
        std::cout << std::endl;
    }

    // Function to display elements in postorder traversal
    void displayPostorder() const {
        std::cout << "Postorder: ";
        postorderTraversal(root);
        std::cout << std::endl;
    }
};

int main() {
    // Example usage of the BinarySearchTree ADT
    BinarySearchTree<int> myBST;

    myBST.insert(50);
    myBST.insert(30);
    myBST.insert(70);
    myBST.insert(20);
    myBST.insert(40);
    myBST.insert(60);
    myBST.insert(80);

    // Display elements in different traversal orders
    myBST.displayPreorder();
    myBST.displayInorder();
    myBST.displayPostorder();

    // Search for elements
    TreeNode<int>* foundNode = myBST.search(40);
    if (foundNode != nullptr) {
        std::cout << "Element 40 found in the BST." << std::endl;
    } else {
        std::cout << "Element 40 not found in the BST." << std::endl;
    }

    // Delete an element
    myBST.deleteNode(30);
    myBST.displayInorder();  // Display elements after deletion

    return 0;
}
