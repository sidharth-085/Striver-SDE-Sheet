#include <iostream>
#include <stack>
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

    ~TreeNode() {
        delete left;
        delete right;
    }
};

// Approach 1: Recursion Based Approach
// Time Complexity: O(N)
// Space Complexity: O(N)

// if we need (node to root) path we can use stack and if we need (root to node) path
// we can use vector.

bool findPath(TreeNode<int> *root, int node, stack<int> &stk) {
    // step 1: check is current root is null or not, if null return false
    if (root == NULL) {
        return false;
    }

    // step 2: add the current root's data to the stack and check if current node
    // is the node which we need, if yess we found the path return true.
    
    stk.push(root->data);
    
    if (root->data == node) {
        return true;
    }

    // step 3: if current node is not, requried node, find path in the left subtree
    // if found, return true else try for right subtree

    bool leftPath = findPath(root->left, node, stk);
    if (leftPath == true) {
        return true;
    }

    bool rightPath = findPath(root->right, node, stk);
    if (rightPath == true) {
        return true;
    }

    // step 4: if either of right or left didn't find the path, pop out the inserted
    // node and return false.

    stk.pop();
    // backtrack and remove the appended node

    return false;
}