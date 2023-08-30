#include <iostream>
using namespace std;

template <typename T>
class TreeNode {
    public:
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;

    TreeNode(T data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

// Approach 1: Recursive Approach (similar to upper bound and lower bound using 
// Binary search)

// Time Complexity: O(N)
// Space Complexity: O(N)

void floorInBSTHelper(TreeNode<int> *root, int x, int &ans) {
    if (root == NULL) {
        return;
    }

    if (root->data == x) { // if the node's value equal to x, return root's value
        ans = root->data;
    }
    else if (root->data < x) { 
        // if node's value is smaller than x, store it in answer, ans try to search
        // bigger value than this in right subtree

        ans = root->data;
        floorInBSTHelper(root->right, x, ans);
    }
    else { // if node's value is bigger than x, search in left side
        floorInBSTHelper(root->left, x, ans);
    }
}

int floorInBST(TreeNode<int> *root, int x) {
    int ans = -1;

    floorInBSTHelper(root, x, ans);

    return ans;
}

// Approach 2: Iterative Approach (similar to upper bound in Binary Search)
// Time Complexity: O(N)
// Space Complexity: O(1)

int floorInBSTHelper(TreeNode<int> *root, int x) {
    if (root == NULL) {
        return;
    }

    TreeNode<int> *temp = root;
    int ans = -1;

    while (temp != NULL) { // iterative method
        if (temp->data  == x) { // if found just break and return the answer
            ans = x;
            break;
        }
        else if (temp->data < x) { // is node's data is smaller, find bigger than noce's value
            ans = temp->data;
            temp = temp->right;
        }
        else { // if node's data is bigger, search in left side for smaller element
            temp = temp->left;
        }
    }

    return ans; // finally return the answer
}

int floorInBST(TreeNode<int> *root, int x) {

    return floorInBSTHelper(root, x);

}