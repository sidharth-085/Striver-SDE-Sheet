#include <iostream>
#include <stack>
using namespace std;

template <typename T>
class BinaryTreeNode {
    public:
    T data;
    BinaryTreeNode<T> *left;
    BinaryTreeNode<T> *right;

    BinaryTreeNode(T data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }

    ~BinaryTreeNode() {
        delete left;
        delete right;
    }
};

// Approach 1: Using Recursion 
// Time Complexity: O(N) & Space Complexity: O(N).
// N is number of nodes in binary tree.

BinaryTreeNode<int>* flattenBinaryTree(BinaryTreeNode<int>*root) {
    if (root == NULL) {
        return NULL;
    }

    BinaryTreeNode<int>* head = new BinaryTreeNode<int>(root->data);
    BinaryTreeNode<int>* left = flattenBinaryTree(root->left);

    if (left != NULL) {
        head->right = left;
    }

    BinaryTreeNode<int>* right = flattenBinaryTree(root->right);

    if (right != NULL) {
        BinaryTreeNode<int>* temp = head;
        while (temp->right != NULL) {
            temp = temp->right;
        }
        temp->right = right;
    }
    return head;
}

// Approach 2: Using Stack 
// Time Complexity: O(N) & Space Complexity: O(N).
// N is number of nodes in binary tree.

BinaryTreeNode<int>* flattenBinaryTree(BinaryTreeNode<int>*root) {
    stack<BinaryTreeNode<int>*> stk;

    BinaryTreeNode<int>* head = root;
    while (root != NULL || !stk.empty()) {
        if (root->right != NULL) {
            stk.push(root->right);
        }

        if (root->left != NULL) {
            // Make the left child as the new right child of the node.
            root->right = root->left;
            root->left = NULL;
        }
        else if (!stk.empty()) {
            // Pop the top node from the stack.
            // Make it the right child of the current node.
            root->right = stk.top();
            stk.pop();
        }

        // Set the right child of the node as the current node.
        root = root->right;
    }

    return head;
}

// Approach 3: Pre-order & Iterative Approach
// Time Complexity: O(N) & Space Complexity: O(N).
// N is number of nodes in binary tree.

void preOrderTraversal(BinaryTreeNode<int>*root, vector<int> &preOrder) {
    if (root == NULL)
        return;

    preOrder.push_back(root->data);

    preOrderTraversal(root->left, preOrder);
    preOrderTraversal(root->right, preOrder);
}

BinaryTreeNode<int>*flattenBinaryTree(BinaryTreeNode<int>*root) {
    vector<int> preOrder;

    // Find the pre-order traversal of the tree and store it in a list.
    preOrderTraversal(root, preOrder);

    // Create a new linked list from the stored values.
    BinaryTreeNode<int>* head = root;

    for (int i = 1; i < preOrder.size(); i++) {
        root->right = new BinaryTreeNode<int>(preOrder[i]);
        root = root->right;
    }

    return head;
}