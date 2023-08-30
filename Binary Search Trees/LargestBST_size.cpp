#include <iostream>
using namespace std;

class TreeNode {
    public:
    int data;
    TreeNode *left, *right;

    TreeNode(int data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

// Approach 1: Brute Force using isBST function && treeSize function
// Time Complexity: O(N^2)
// Space Complexity: O(N)

bool isBSTHelper(TreeNode *root, int min, int max) {
    if (root == NULL) {
        return true;
    }

    if (root->data > max || root->data < min) {
        return false;
    }

    bool leftBST = isBSTHelper(root->left, min, root->data - 1);
    bool rightBST = isBSTHelper(root->right, root->data, max);

    return leftBST && rightBST;
}

bool isBST(TreeNode *root) { // function to check is given tree is BST or not
    return isBSTHelper(root, INT_MIN, INT_MAX);
} 

int treeSize(TreeNode *root) { // function to calculate size of the tree 
    if (root == NULL) {
        return 0;
    }

    int leftCount = treeSize(root->left);
    int rightCount = treeSize(root->right);

    return leftCount + rightCount + 1;
}

int largestBST_size(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    // now check is current tree is bst or not
    bool rootBST = isBST(root);
    if (rootBST == true) { 
        // if current tree is bst return its size
        return treeSize(root);
    }

    // if not, check for right side and left side's largest BST size

    int leftBSTsize = largestBST_size(root->left);
    int rightBSTsize = largestBST_size(root->right);
    
    return max(leftBSTsize, rightBSTsize); // return whichever is maximum
}

// Approach 2: Better Approach
// Time Complexity: O(N)
// Space Complexity: O(N)

// find isBST, max and min for isBST func and size of tree together

class info { // class for storing the information of particular tree below the node
    public: 
    int maxOfTree;
    int minOfTree;
    bool isBST;
    int sizeOfBST;
};

info largestBSThelper(TreeNode *root) {
    info ans;
    
    // step 1: base case
    if (root == NULL) {
        ans.minOfTree = INT_MAX;
        ans.maxOfTree = INT_MIN;
        ans.isBST = true;
        ans.sizeOfBST = 0;

        return ans;
    }

    // step 2: bring answer from left subtree and right subtree for isBST, min, max.

    info leftAns = largestBSThelper(root->left);
    info rightAns = largestBSThelper(root->right);

    // step 3: find max and min of current tree

    ans.maxOfTree = max(root->data, max(leftAns.maxOfTree, rightAns.maxOfTree));
    ans.minOfTree = min(root->data, min(leftAns.minOfTree, rightAns.minOfTree));

    // step 4: now, check is current tree is BST or not, if yes mark isBST for ans true
    // and the size of BST as sum of both left and right subtree size + 1 (due to root).

    if ((leftAns.isBST) && (rightAns.isBST) && (root->data > leftAns.maxOfTree) 
        && (root->data <= rightAns.minOfTree)) {
        
        ans.isBST = true;
        ans.sizeOfBST = leftAns.sizeOfBST + rightAns.sizeOfBST + 1;

    }
    // else mark isBST as false and size of BST as maximum of left and right subtrees
    else {
        ans.isBST = false;
        ans.sizeOfBST = max(leftAns.sizeOfBST, rightAns.sizeOfBST);
    }

    return ans;
}

int largestBST_size(TreeNode* root) {
    info ans = largestBSThelper(root);

    return ans.sizeOfBST;
}