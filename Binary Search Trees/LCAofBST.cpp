#include <iostream>
#include <stack>
using namespace std;

// Same problem as for Binary Tree but we can use the property of BST

class TreeNode {
    public: 
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int data) {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

// Approach 1: Brute Force using Stacks (same for Binary Tree we used)
// Time Complexity: O(N)
// Space Complexity: O(N)

bool findPath(TreeNode *root, TreeNode *node, stack<TreeNode*> &stk) {
    if (root == NULL) {
        return false;
    }

    stk.push(root);

    if (root->data == node->data) {
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

TreeNode *LCAinaBST(TreeNode *root, TreeNode *x, TreeNode *y) {
    if (root == NULL) {
        return NULL;
    }

    // find paths for both nodes x and y and store in the stacks

    stack<TreeNode*> stkX;
    stack<TreeNode*> stkY;

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

    while (stkX.top()->data != stkY.top()->data) {
        stkX.pop();
        stkY.pop();
    }

    // finally return the top element which is equal

    return stkX.top();
}

// Approach 2: Recursion with Space Optimization
// Time Complexity: O(N)
// Space Complexity: O(N)

TreeNode *LCAinaBST(TreeNode *root, TreeNode *P, TreeNode *Q) {
    if (root == NULL) {
        return NULL;
    }

    if (root->data == P->data || root->data == Q->data) {
        return root;
    }

    TreeNode *leftLCA = LCAinaBST(root->left, P, Q);

    TreeNode *rightLCA = LCAinaBST(root->right, P, Q);

    if (leftLCA && rightLCA) {
        return root;
    }

    else if (leftLCA) {
        return leftLCA;
    }

    else if (rightLCA) {
        return rightLCA;
    }

    return NULL;
}

// Approach 3: Use the property of BST
// Time Complexity: O(N)
// Space Complexity: O(N)

TreeNode *LCAinaBST(TreeNode *root, TreeNode *P, TreeNode *Q) {
    // step 1: check is root is NULL or not
    
    if (root == NULL) {
        return NULL;
    }

    // step 2: by using property of BST, check is both P and Q are smaller than root
    // if yes, try searching for LCA in left

    if (root->data > P->data && root->data > Q->data) {
        return LCAinaBST(root->left, P, Q);
    }

    // step 3: check is both P and Q are bigger than root, if yes try searching for LCA
    // in right

    else if (root->data < P->data && root->data < Q->data) {
        return LCAinaBST(root->right, P, Q);
    }

    // step 4: if P is smaller than root and Q is bigger than root or vice versa for 
    // both cases, if this is the case root is the LCA for given two nodes

    else {
        return root;
    }
}

// Approach 4: Iterative Approach 
// Time Complexity: O(N)
// Space Complexity: O(1)

TreeNode *LCAinaBST(TreeNode *root, TreeNode *P, TreeNode *Q) {
    // step 1: check is root is NULL or not
    if (root == NULL) {
        return NULL;
    }

    TreeNode *curr = root;

    while (curr != NULL) {
        // step 2: by using property of BST, check is both P and Q are smaller than 
        // root if yes, try searching for LCA in left

        if (curr->data > P->data && curr->data > Q->data) {
            curr = curr->left;
        }

        // step 3: check is both P and Q are bigger than root, if yes try searching for
        // LCA in right

        else if (curr->data < P->data && curr->data < Q->data) {
            curr = curr->right;
        }
        // step 4: if P is smaller than root and Q is bigger than root or vice versa 
        // for both cases, if this is the case root is the LCA for given two nodes

        else {
            return curr;
        }
    }

    return NULL;
}