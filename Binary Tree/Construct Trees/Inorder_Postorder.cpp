#include <iostream>
#include <unordered_map>
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

// Approach 1: Recursive Approach
// Time Complexity: O(N^2)
// Space Complexity: O(N)

TreeNode<int> *buildTree(vector<int> &inorder, vector<int> &postorder, int inS, int inE, int postS, int postE) {
    if (inS > inE || postS > postE) {
        return NULL;
    }

    int rootData = postorder[postE];

    TreeNode<int> *root = new TreeNode<int>(rootData);

    int rootIndex = 0;
    while (inorder[rootIndex] != rootData) {
        rootIndex++;
    }

    int numLeft = rootIndex - inS; // number of elements in left subtree

    root->left = buildTree(inorder, postorder, inS, rootIndex - 1, postS, postS + numLeft - 1);

    root->right = buildTree(inorder, postorder, rootIndex + 1, inE, postS + numLeft, postE - 1);

    return root;
}

TreeNode<int> *buildBinaryTree(vector<int> &inorder, vector<int> &postorder) {
    return buildTree(inorder, postorder, 0, inorder.size() - 1, 0, postorder.size() - 1);
}

// Approach 2: Using Hashmap 
// Time Complexity: O(N)
// Space Complexity: O(N)

TreeNode<int> *buildTree(vector<int> &inorder, vector<int> &postorder, int inS, int inE, int postS, int postE, unordered_map<int, int> &inorderMap) {
    if (inS > inE || postS > postE) {
        return NULL;
    } 

    int rootData = postorder[postE];

    TreeNode<int> *root = new TreeNode<int>(rootData);

    int rootIndex = inorderMap[rootData];

    int numLeft = rootIndex - inS;

    root->left = buildTree(inorder, postorder, inS, rootIndex - 1, postS, postS + numLeft - 1, inorderMap);
    
    root->right = buildTree(inorder, postorder, rootIndex + 1, inE, postS + numLeft, postE - 1, inorderMap);

    return root;
}

TreeNode<int> *buildBinaryTree(vector<int> &inorder, vector<int> &postorder) {
    unordered_map<int, int> inorderMap;

    for (int i=0; i<inorder.size(); i++) {
        inorderMap[inorder[i]] = i;
    }

    return buildTree(inorder, postorder, 0, inorder.size() - 1, 0, postorder.size() - 1, inorderMap);
}