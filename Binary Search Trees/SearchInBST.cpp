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

// Iterative Approach

bool searchInBST(BinaryTreeNode<int> *root, int x) {
    if (root == NULL) {
        return false;
    }

    BinaryTreeNode<int> *temp = root;
    while (temp != NULL && temp->data != x) {
        if (temp->data > x) {
            temp = temp->left;
        }
        else {
            temp = temp->right;
        }
    }
    if (temp == NULL) {
        return false;
    }
    return true;
}

// Recursive Approach

bool searchInBST(BinaryTreeNode<int> *root, int x) {
    if (root==NULL) {
        return false;
    }

    if (root->data > x) {
        return searchInBST(root->left, x);
    }
    else if (root->data < x) {
        return searchInBST(root->right, x);
    }
    else {
        return true;
    }
    return false;
}