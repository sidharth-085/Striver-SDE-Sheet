#include <iostream>
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
// Time Complexity: O(N*N)
// Space Complexity: O(N)
// N is number of nodes in Binary Tree

BinaryTreeNode<int>* BTtoDLL(BinaryTreeNode<int>* root) {
    if (root == NULL) { // base case
        return NULL;
    }
    
    if (root->left == NULL && root->right == NULL) { // if we reached at leaf node
        return root;
    }

    // first make left subtree as doubly linkedlist.
    BinaryTreeNode<int> *leftLL = BTtoDLL(root->left); 

    if (leftLL != NULL) { // if left subtree LL is not empty
        BinaryTreeNode<int> *temp = leftLL; 
        // go to the rightmost node of Left subtree LL

        while (temp->right != NULL) {
            temp = temp->right;
        } 

        temp->right = root; // insert root at right of rightmost node.
        root->left = temp; // insert rightmost node at left of root node.
    }
    else {
        root->left = NULL; 
        // if left subtree LL is null, then just insert NULL at left of root.
    }

    BinaryTreeNode<int> *rightLL = BTtoDLL(root->right);
    // then make right subtree as doubly linkedlist.

    if (rightLL != NULL) { // if right subtree is not empty
        rightLL->left = root; // insert root at left of rightLL head
        root->right = rightLL; // insert right subtree LL at right of root.
    }
    else {
        root->right = NULL;
        // else insert null at right of root
    }

    while (root->left != NULL) { 
        // then, go to the leftmost node, which is starting node for new doubly linkedlist
        root = root->left;
    }

    return root; // then just return root.
}

// Approach 2: Using In-Order Traversal of Binary Tree
// Time Complexity: O(N)
// Space Complexity: O(N)

void helperFunc(BinaryTreeNode<int> *root, BinaryTreeNode<int>* &head, BinaryTreeNode<int>* &prev) {
    if (root == NULL) {
        return;
    }

    // start work on left subtree
    helperFunc(root->left, head, prev); // get the answer from left first

    // start work on root
    if (prev == NULL) {
        head = root;
    }
    else {
        root->left = prev; // insert prev at left of root
        prev->right = root; // and, insert root at right of prev
    }

    prev = root;

    // start work on right subtree
    helperFunc(root->right, head, prev);
} 

BinaryTreeNode<int>* BTtoDLL(BinaryTreeNode<int>* root) {
    BinaryTreeNode<int> *head = NULL;
    BinaryTreeNode<int> *prev = NULL;

    helperFunc(root, head, prev);

    return head;
}