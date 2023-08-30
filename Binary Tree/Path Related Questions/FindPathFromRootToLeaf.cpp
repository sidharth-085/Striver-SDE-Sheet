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
};

// Approach using Pre-order traversal
// Time Complexity: O(N)
// Space Complexity: O(N)

bool findPath(TreeNode<int> *root, TreeNode<int> *leaf, stack<TreeNode<int>*> &stk) {
    // step 1: check for base case

    if (root == NULL) {
        return false;
    }

    // step 2: start the pre-order traversal on binary tree.

    stk.push(root); // push the root in the stack.

    // check is the current node is leadf node or not

    if (root->left == NULL && root->right == NULL) {
        // if current node is leaf node, the check is this is same as given node

        if (root->data == leaf->data) {
            return true;
        }
        else { // if not, pop the node from stack and return false.
            stk.pop();
            return false;
        }
    }

    // step 3: now if current node is not leaf node, check on both subtrees

    bool leftAns = findPath(root->left, leaf, stk); // try checking in left side
    if (leftAns == true) {
        return true;
    }

    bool rightAns = findPath(root->right, leaf, stk); // try checking in right side
    if (rightAns == true) {
        return true;
    }

    stk.pop(); // if not found in both sides, pop the node from stack and return false.

    return false;
}