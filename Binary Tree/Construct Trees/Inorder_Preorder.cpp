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

TreeNode<int> *buildTree(vector<int> &inorder, vector<int> &preorder, int inS, int inE, int preS, int preE) {
    // step 1: if start index becomes bigger than end index, return NULL
    
    if (inS > inE || preS > preE) {
        return NULL;
    }

    // step 2: pre-order first value is root of the current tree

    int rootData = preorder[preS];
    TreeNode<int> *root = new TreeNode<int>(rootData); 
    // make the root for the current tree from preorder first value

    // step 3: now find the index where root data is present in inorder

    int rootIndex = inS;
    while (inorder[rootIndex] != rootData) {
        rootIndex++;
    }
 
    int numLeft = rootIndex - inS; // num of elements in left subtree

    root->left = buildTree(inorder, preorder, inS, rootIndex - 1, preS + 1, preS + numLeft);

    root->right = buildTree(inorder, preorder, rootIndex + 1, inE, preS + numLeft + 1, preE);

    return root; // finally return root
}

TreeNode<int> *buildBinaryTree(vector<int> &inorder, vector<int> &preorder) {
    return buildTree(inorder, preorder, 0, inorder.size() - 1, 0, preorder.size() - 1);
}

// Approach 2: Using Hashmap Approach with recursion
// Time Complexity: O(N)
// Space Complexity: O(N)

// this avoids the loop searching for root everytime in each recursive call

TreeNode<int>* buildTree(vector<int> &inorder, vector<int> &preorder, int inS, int inE, int preS, int preE, unordered_map<int, int> &inorderMap) {
    // step 1: if start index becomes bigger than end index, return NULL
    
    if (inS > inE || preS > preE) {
        return NULL;
    }

    // step 2: pre-order first value is root of the current tree

    int rootData = preorder[preS];
    TreeNode<int> *root = new TreeNode<int>(rootData); 
    // make the root for the current tree from preorder first value

    // step 3: now find the index where root data is present in inorder

    int rootIndex = inorderMap[rootData];

    int numLeft = rootIndex - inS;

    root->left = buildTree(inorder, preorder, inS, rootIndex - 1, preS + 1, preS + numLeft, inorderMap);

    root->right = buildTree(inorder, preorder, rootIndex + 1, inE, preS + numLeft + 1, preE, inorderMap);

    return root; // finally return root
}

TreeNode<int> *buildBinaryTree(vector<int> &inorder, vector<int> &preorder) {
    // we will store every value of inorder as key and index as value in map

    unordered_map<int, int> inorderMap;

    for (int i=0; i<inorder.size(); i++) {
        inorderMap[inorder[i]] = i;
    }

    return buildTree(inorder, preorder, 0, inorder.size() - 1, 0, preorder.size() - 1, inorderMap);
}