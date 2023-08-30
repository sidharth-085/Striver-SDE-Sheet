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

// Approach 1: Recursive Approach
// Time Complexity: O(N)
// Space Complexity: O(N)

void helper(BinaryTreeNode<int> *root, int x, int &ans) {
    if (root == NULL) {
        return;
    }

    if (root->data == x) {
        ans = x;
        return;
    }
    // if we found the first element which is bigger than x, search for smaller.
    else if (root->data > x) { 
        ans = root->data;
        helper(root->left, x, ans);
    }
    else { // if not found, go to right and find
        helper(root->right, x, ans);
    }
}

int findCeil(BinaryTreeNode<int> *root, int x) {
    if (root == NULL) {
        return -1;
    }

    int ans = -1;
    helper(root, x, ans);

    return ans;
}

// Approach 2: Iterative Approach
// Time Complexity: O(N)
// Space Complexity: O(N)

int findCeil(BinaryTreeNode<int> *root, int x) {
    if (root == NULL) {
        return -1;
    }

    int ans = -1;

    BinaryTreeNode<int> *temp = root;

    while (temp != NULL) {
        if (temp->data == x) {
            return x;
        }
        // if we found the first element which is bigger than x, search for smaller.
        else if (temp->data > x) { 
            ans = temp->data;
            temp = temp->left;
        }
        else { // if not found, search in right
            temp = temp->right;
        }
    }

    return ans;
}