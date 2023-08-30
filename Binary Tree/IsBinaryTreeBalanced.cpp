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

// Approach 1: Brute Force
// Time Complexity: O(N^2)
// Space Complexity: O(N)
 
int getHeight(TreeNode<int> *root) { // find height function of tree
    if (root == NULL) {
        return 0;
    }

    int left = getHeight(root->left);
    int right = getHeight(root->right);

    return max(left, right) + 1;
}

bool isBalancedBT(TreeNode<int>* root) {
    if (root == NULL) {
        return true;
    }
    
    int leftHeight = getHeight(root->left); // calculate left subtree height

    int rightHeight = getHeight(root->right); // calculate right subtree height

    return isBalancedBT(root->left) && isBalancedBT(root->right) && (abs(leftHeight - rightHeight) <= 1);
    // left and right subtrees should be balanced and difference of left and right height
    // is less than or equal to 1.
}

// Approach 2: Optimized Approach
// Time Complexity: O(N)
// Space Complexity: O(N)

// this function find both height and is current subtree is balanced together

pair<int, bool> helper(TreeNode<int> *root) {
    if (root == NULL) {
        return {0, true}; // if tree is empty, height is 0 and it is balanced
    }

    pair<int, bool> leftAns = helper(root->left); 
    // pair of left height and is left subtree is balanced 

    pair<int, bool> rightAns = helper(root->right);
    // pair of right height and is right subtree is balanced 

    pair<int, bool> ans;
    ans.first = max(leftAns.first, rightAns.first) + 1; 
    // height of current tree

    ans.second = (leftAns.second == true) && (rightAns.second == true) && 
                 (abs(leftAns.first - rightAns.first) <= 1);
    // is current tree is balanced or not

    return ans;
}

bool isBalancedBT(TreeNode<int>* root) {
    pair<int, bool> ans = helper(root);

    return ans.second;
}