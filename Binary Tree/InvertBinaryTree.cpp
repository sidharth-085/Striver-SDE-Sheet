#include <iostream>
#include <stack>
using namespace std;

// Question is saying that invert the binary tree in such a way that:

// 1. If parent exists on the right side and left has some node, first transfer the 
// left node to right and make he left side null. And, then link the currNode with
// parent.

// 2. If parent exists on the left side, make the left side null && insert the currNode 
// in the left of parent node and update parent.

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

// Approach using Pre-order traversal of Binary Tree
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

TreeNode<int>* invertBinaryTree(TreeNode<int> *root, TreeNode<int> *leaf) {
    // step 1: check is root is null or not

    if (root == NULL) {
        return NULL;
    }

    // step 2: find the path from root to the given leaf node and store in stack

    stack<TreeNode<int>*> stk;
    findPath(root, leaf, stk);

    // step 3: now we get the stack of path from root to leaf, top node of stack is the
    // new root.

    TreeNode<int> *newRoot = stk.top();
    stk.pop();

    TreeNode<int> *parent = newRoot; 
    // newRoot is the parent we have to start the inversion

    while (!stk.empty()) {
        TreeNode<int> *currNode = stk.top(); // take out the top node from stack
        stk.pop();

        // condition 1: if parent exists on left side, we have to just make left
        // side of currentNode null, and make the currentNode as left child of parent

        if (currNode->left == parent) { 
            currNode->left = NULL;
            parent->left = currNode;
        }
        // condition 2: if parent exists on right side, we have to make left child of
        // current node as right child and then make left child of currentNode as null
        // and currentNode as left child of parent
        else {
            currNode->right = currNode->left;
            currNode->left = NULL;
            parent->left = currNode;
        }

        parent = currNode; // finally move the parent to the currentNode.
    }

    return newRoot;
}