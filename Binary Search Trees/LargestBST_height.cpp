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

// Approach 1: Brute Force using isBST function && getHeight function
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

int getHeight(TreeNode *root) { // function for finding height of tree
    if (root == NULL) {
        return 0;
    }

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    return max(leftHeight, rightHeight) + 1;
}

int largestBST_height(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    // now check is current tree is bst or not
    bool rootBST = isBST(root);
    if (rootBST == true) { 
        // if current tree is bst return its height
        return getHeight(root);
    }

    // if not, check for right side and left side's largest BST height

    int leftBST_height = largestBST_height(root->left);
    int rightBST_height = largestBST_height(root->right);
    
    return max(leftBST_height, rightBST_height); // return whichever is maximum
}

// Approach 2: find the isBST, max, min and height of BST together
// Time Complexity: O(N)
// Space Complexity: O(N)

class info { // class for storing the information of particular tree below the node
    public: 
    int maxOfTree;
    int minOfTree;
    bool isBST;
    int heightOfBST;
};

info largestBST_helper(TreeNode *root) {
    info ans;
    
    // step 1: base case
    if (root == NULL) {
        ans.minOfTree = INT_MAX;
        ans.maxOfTree = INT_MIN;
        ans.isBST = true;
        ans.heightOfBST = 0;

        return ans;
    }

    // step 2: bring answer from left subtree and right subtree for isBST, min, max.

    info leftAns = largestBST_helper(root->left);
    info rightAns = largestBST_helper(root->right);

    // step 3: find max and min of current tree

    ans.maxOfTree = max(root->data, max(leftAns.maxOfTree, rightAns.maxOfTree));
    ans.minOfTree = min(root->data, min(leftAns.minOfTree, rightAns.minOfTree));

    // step 4: now, check is current tree is BST or not, if yes mark isBST for ans true
    // and the height of BST as max of left and right subtree size + 1 (due to root).

    if ((leftAns.isBST) && (rightAns.isBST) && (root->data > leftAns.maxOfTree) 
        && (root->data <= rightAns.minOfTree)) {
        
        ans.isBST = true;
        ans.heightOfBST = max(leftAns.heightOfBST, rightAns.heightOfBST) + 1;

    }
    // else mark isBST as false and height of BST as maximum of left and right subtrees
    else {
        ans.isBST = false;
        ans.heightOfBST = max(leftAns.heightOfBST, rightAns.heightOfBST);
    }

    return ans;
}

int largestBST_size(TreeNode* root) {
    info ans = largestBST_helper(root);

    return ans.heightOfBST;
}