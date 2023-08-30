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

    ~TreeNode() {
        delete left;
        delete right;
    }
};

// Maximum Path sum is the maximum sum between to leaf nodes and steps to calculate 
// this are:

// 1. find the maximum sum path for left subtree from leaf to a node.
// 2. find the maximum sum path for right subtree from leaf to a node.
// 3. add above calculated values together with root's data to calculate the maximum
//    path sum
// 4. Now, call recursion on left subtree and right subtree and compare with the 
//    combined answer and whichever is maximum return it.

// Approach 1: Brute Force Solution
// Time Complexity: O(N^2)
// Space Complexity: O(N)

// function to calculate maximum sum path from leaf to node separately 
long long int findMaxSumNodeToLeaf(TreeNode<int> *root) {
    if (root == NULL) {
        return 0;
    }

    long long int leftAns = findMaxSumNodeToLeaf(root->left);
    long long int rightAns = findMaxSumNodeToLeaf(root->right);

    return root->data + max(leftAns, rightAns); // similar to height of the tree
}

// function to calculate maximum path sum
long long int findMaxPathSumViaNode(TreeNode<int> *root) {
    if (root == NULL) {
        return INT_MIN; // in starting maximum sum is minimum as possible
    }

    // calculate maximum sum path for left and right subtree
    long long int leftMaxSumNodeToLeaf = findMaxSumNodeToLeaf(root->left);
    long long int rightMaxSumNodeToLeaf = findMaxSumNodeToLeaf(root->right);

    // add both with current node's data
    long long int currMaxPathSumViaNode = root->data + leftMaxSumNodeToLeaf + rightMaxSumNodeToLeaf;

    // call recursion and find ans for left subtree and right subtree
    long long int leftAns = findMaxPathSumViaNode(root->left);
    long long int rightAns = findMaxPathSumViaNode(root->right);

    // at last compare all three values, which ever gives maximum answer will be the answer
    return max({leftAns, rightAns, currMaxPathSumViaNode});
}

long long int findMaxSumPath(TreeNode<int> *root) {
    if (root == NULL) { // if current tree is empty, return -1.
        return -1;
    }

    // if any of child is null, answer is -1
    if (root->left == NULL || root->right == NULL) { 
        return -1;
    }

    return findMaxPathSumViaNode(root);
}

// Approach 2: Better Approach Calculating Max sum from node to leaf and maximum sum 
// path between two leaves together.

// Time Complexity: O(N)
// Space Complexity: O(N)

class Info { // class for storing maxSumNodeToLeaf and maxSumPath together
    public:
    long long int maxSumNodeToLeaf;
    long long int maxSumPath;
};

Info helper(TreeNode<int> *root) {
    if (root == NULL) {
        return {0LL, INT_MIN};
    }  

    // in this method, we are finding both values
    Info leftAns = helper(root->left);
    long long int leftMaxSumNodeToLeaf = max(0LL, leftAns.maxSumNodeToLeaf);
    // checking if the node to leaf max sum is negative dont take it, take 0 instead

    Info rightAns = helper(root->right);
    long long int rightMaxSumNodeToLeaf = max(0LL, rightAns.maxSumNodeToLeaf);
    // checking if the node to leaf max sum is negative dont take it, take 0 instead

    long long int currMaxSumNodeToLeaf = root->data + max(leftMaxSumNodeToLeaf, rightMaxSumNodeToLeaf);
    long long int currMaxSumPath = max({root->data + leftMaxSumNodeToLeaf + rightMaxSumNodeToLeaf, leftAns.maxSumPath, rightAns.maxSumPath});

    return {currMaxSumNodeToLeaf, currMaxSumPath};
}

long long int findMaxSumPath(TreeNode<int> *root) {
    if (root == NULL) {
        return -1;
    }

    if (root->left == NULL || root->right == NULL) {
        return -1;
    }

    Info finalAns = helper(root);

    return finalAns.maxSumPath;
}

// Approach 2: Using Optimal Approach using Backtracking and finding the longest path
// sum and maximum path sum together

// Time Complexity: O(N)
// Space Complexity: O(N)

long long int findMaxSumNodeToLeaf(TreeNode<int> *root, long long int &maxi) {
    if (root == NULL) {
        return 0;
    }

    // checking if the node to leaf max sum is negative dont take it, take 0 instead
    long long int leftMaxPath = max(0LL, findMaxSumNodeToLeaf(root->left, maxi));
    long long int rightMaxPath = max(0LL, findMaxSumNodeToLeaf(root->right, maxi));

    long long int maxSumPath = root->data + leftMaxPath + rightMaxPath;
    maxi = max(maxi, maxSumPath);
    // backtracking and storing the maximum sum value 

    return root->data + max(leftMaxPath, rightMaxPath);
}

long long int findMaxSumPath(TreeNode<int> *root) {
    if (root == NULL) {
        return -1;
    }

    if (root->left == NULL || root->right == NULL) {
        return -1;
    }

    long long int maxi = INT_MIN;
    
    findMaxSumNodeToLeaf(root, maxi);

    return maxi;
}