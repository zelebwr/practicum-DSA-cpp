#include <iostream>

// Use the standard namespace as requested
using namespace std;

// Class definition for the AVL Tree
class AVLTree
{
private:
    // Structure for the nodes of the AVL tree
    struct AVLNode
    {
        int capacity; // The capacity of the item
        int height;   // Height of the node in the tree
        int count;    // How many items of this capacity exist
        AVLNode *left, *right;
    };

    AVLNode *_root;
    unsigned int _size;

    // Helper function to get the maximum of two integers
    int _max(int a, int b) const
    {
        return (a > b) ? a : b;
    }

    // Helper function to get the height of a node
    // Returns -1 if the node is null
    int _getHeight(AVLNode* node) const
    {
        if (node == nullptr)
            return -1;
        return node->height;
    }

    // Updates the height of a node based on its children's heights
    void _updateHeight(AVLNode* node) {
        if (node != nullptr) {
            node->height = 1 + _max(_getHeight(node->left), _getHeight(node->right));
        }
    }

    // Helper function to get the balance factor of a node
    int _getBalanceFactor(AVLNode* node) const
    {
        if (node == nullptr)
            return 0;
        return _getHeight(node->left) - _getHeight(node->right);
    }

    // Performs a right rotation on the given pivot node
    AVLNode* _rightRotate(AVLNode* pivotNode)
    {
        AVLNode* newRoot = pivotNode->left;
        pivotNode->left = newRoot->right;
        newRoot->right = pivotNode;

        _updateHeight(pivotNode);
        _updateHeight(newRoot);

        return newRoot;
    }

    // Performs a left rotation on the given pivot node
    AVLNode* _leftRotate(AVLNode* pivotNode)
    {
        AVLNode* newRoot = pivotNode->right;
        pivotNode->right = newRoot->left;
        newRoot->left = pivotNode;

        _updateHeight(pivotNode);
        _updateHeight(newRoot);

        return newRoot;
    }

    // Performs rebalancing on a node after an operation
    AVLNode* _rebalance(AVLNode* node) {
        if (node == nullptr) return node;

        _updateHeight(node);
        int balance = _getBalanceFactor(node);

        // Left-heavy case
        if (balance > 1) {
            // Left-Right case
            if (_getBalanceFactor(node->left) < 0) {
                node->left = _leftRotate(node->left);
            }
            // Left-Left case
            return _rightRotate(node);
        }
        // Right-heavy case
        if (balance < -1) {
            // Right-Left case
            if (_getBalanceFactor(node->right) > 0) {
                node->right = _rightRotate(node->right);
            }
            // Right-Right case
            return _leftRotate(node);
        }
        return node;
    }

    // Function to create a new AVL node
    AVLNode* _createNode(int value)
    {
        AVLNode* newNode = new AVLNode;
        newNode->capacity = value;
        newNode->height = 0;
        newNode->count = 1;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    // Recursive function to insert a value into the AVL tree
    AVLNode* _insert_recursive(AVLNode* node, int value)
    {
        if (node == nullptr) {
            _size++;
            return _createNode(value);
        }

        if (value < node->capacity) {
            node->left = _insert_recursive(node->left, value);
        } else if (value > node->capacity) {
            node->right = _insert_recursive(node->right, value);
        } else {
            // Value already exists, just increment the count
            node->count++;
        }

        return _rebalance(node);
    }

    // Function to find the minimum node in a subtree
    AVLNode* _findMinNode(AVLNode *node) const
    {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // Recursive function to remove a value from the AVL tree
    AVLNode* _remove_recursive(AVLNode* node, int value)
    {
        if (node == nullptr) return node;

        if (value < node->capacity) {
            node->left = _remove_recursive(node->left, value);
        } else if (value > node->capacity) {
            node->right = _remove_recursive(node->right, value);
        } else {
            // Node with the value found
            if (node->count > 1) {
                node->count--;
                return node; // No structural change needed
            }

            _size--;
            // Node with one or zero children
            if (node->left == nullptr || node->right == nullptr) {
                AVLNode* temp = node->left ? node->left : node->right;
                if (temp == nullptr) { // No child
                    temp = node;
                    node = nullptr;
                } else { // One child
                    *node = *temp;
                }
                delete temp;
            } else {
                // Node with two children
                AVLNode* temp = _findMinNode(node->right);
                node->capacity = temp->capacity;
                node->count = temp->count;
                // We've moved the data, now delete the original node
                // from which the data was moved.
                node->right = _remove_recursive(node->right, temp->capacity);
                // The recursive call above might have changed the count of the moved node,
                // so we restore it here to avoid losing items.
                temp->count = 1; // Set it back to 1 before it's actually removed
            }
        }
        
        return _rebalance(node);
    }

    // Recursive function to destroy the AVL tree
    void _destroyRecursive(AVLNode* node)
    {
        if (node) {
            _destroyRecursive(node->left);
            _destroyRecursive(node->right);
            delete node;
        }
    }

    // Recursive function to find the best fit for a requirement
    int _findBestFitRecursive(AVLNode* node, int requirement, int bestFit) const {
        if (node == nullptr) {
            return bestFit;
        }

        if (node->capacity >= requirement) {
            // This node is a potential candidate. It's better than the current bestFit
            // if it's smaller, but still meets the requirement.
            bestFit = node->capacity;
            // Since we found a potential fit, we try to find an even better (smaller) one
            // in the left subtree.
            return _findBestFitRecursive(node->left, requirement, bestFit);
        } else {
            // This node's capacity is too small. We must look in the right subtree
            // for a larger capacity.
            return _findBestFitRecursive(node->right, requirement, bestFit);
        }
    }

public:
    AVLTree() : _root(nullptr), _size(0u) {}

    ~AVLTree()
    {
        _destroyRecursive(_root);
    }

    // Public function to insert a value
    void insert(int value)
    {
        _root = _insert_recursive(_root, value);
    }

    // Public function to remove a value
    void remove(int value)
    {
        _root = _remove_recursive(_root, value);
    }

    // Public function to find the best-fit item for a given requirement.
    // Returns the capacity of the item, or -1 if no suitable item is found.
    int findBestFit(int requirement) {
        int bestFit = -1;
        return _findBestFitRecursive(_root, requirement, bestFit);
    }
};

int main()
{
    // Disable synchronization with stdio for faster I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    AVLTree storage;
    int Q;
    cin >> Q;

    char command;
    int value;

    for (int i = 0; i < Q; ++i) {
        cin >> command >> value;
        if (command == 'i') {
            storage.insert(value);
        } else if (command == 'j') {
            int bestFitItem = storage.findBestFit(value);
            cout << bestFitItem << "\n";
            if (bestFitItem != -1) {
                storage.remove(bestFitItem);
            }
        }
    }

    return 0;
}
