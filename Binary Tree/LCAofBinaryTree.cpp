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

// Approach 1: Using the Path finding for both nodes using stack and then find the LCA 
// Time Complexity: O(N)
// Space Complexity: O(N)

bool findPath(TreeNode<int> *root, int node, stack<int> &stk) {
    if (root == NULL) {
        return false;
    }

    stk.push(root->data);

    if (root->data == node) {
        return true;
    }

    bool leftPath = findPath(root->left, node, stk);
    if (leftPath) {
        return true;
    }

    bool rightPath = findPath(root->right, node, stk);
    if (rightPath) {
        return true;
    }

    stk.pop();
    return false;
}

int lowestCommonAncestor(TreeNode<int> *root, int x, int y) {
    if (root == NULL) {
        return -1;
    }

    // find paths for both nodes x and y and store in the stacks

    stack<int> stkX;
    stack<int> stkY;

    findPath(root, x, stkX);

    findPath(root, y, stkY);

    // make the size of stacks equal first

    if (stkX.size() > stkY.size()) { // if first stack is bigger, pop nodes for first
        while (stkX.size() != stkY.size()) {
            stkX.pop();
        }
    }
    else { // if second stack is bigger, pop nodes for second
        while (stkY.size() != stkX.size()) {
            stkY.pop();
        }
    }

    // finally traverse the stack and check if any two top elements are equal, if yes
    // it is the LCA because we are traversing from bottom to top, so the first node 
    // which is equal, it is the LCA

    while (stkX.top() != stkY.top()) {
        stkX.pop();
        stkY.pop();
    }

    // finally return the top element which is equal

    return stkX.top();
}

// Approach 2: Space Optimized Approach
// Time Complexity: O(N)
// Space Complexity: O(N)

TreeNode<int> *LCA(TreeNode<int> *root, int x, int y) {
    // step 1: check is current node is null or not

    if (root == NULL) {
        return NULL;
    }

    // step 2: check if the current node is x or y, means the LCA is same as root

    if (root->data == x || root->data == y) {
        return root;
    }

    // step 3: if current node is not equal to x or y, find the LCA for left subtree
    // and right subtree separately

    TreeNode<int> *leftLCA = LCA(root->left, x, y);

    TreeNode<int> *rightLCA = LCA(root->right, x, y);

    // step 4: if lca of left subtree and right subtree both are non null, means 
    // we are standing at the current node is the LCA of the binary tree i.e. root
    
    if (leftLCA != NULL && rightLCA != NULL) {
        return root;
    }

    // step 5: if rightLCA is null and leftLCA is not null, means leftLCA is the 
    // LCA of the binary tree

    if (leftLCA != NULL) {
        return leftLCA;
    }

    // step 6: if leftLCA is null and rightLCA is not null, means rightLCA is the 
    // LCA of the binary tree

    if (rightLCA != NULL) {
        return rightLCA;
    }

    // step 7: if none of the case matches answer is NULL.

    return NULL;
}

int lowestCommonAncestor(TreeNode<int> *root, int x, int y) {
    TreeNode<int> *lca = LCA(root, x, y);

    return lca->data;
}