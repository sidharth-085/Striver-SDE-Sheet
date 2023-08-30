#include <iostream>
#include <unordered_map>
using namespace std;

class TreeNode {
    public: 

    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Approach 1: Using Recursion without hashmap
// Time Complexity: O(N^2)
// Space Complexity: O(N)

TreeNode* buildTree(vector<int>& preorder, vector<int>& postorder, int preS, int preE, int postS, int postE) {
    // step 1: base case
    if (preS > preE || postS > postE) {
        return NULL;
    }
    
    // step 2: make root from pre-order first element

    int rootData = preorder[preS];
    TreeNode* root = new TreeNode(rootData);

    // step 3: check is preS + 1 is out of bounds or not

    if (preS + 1 > preE) {
        return root;
    }

    // step 4: now find the first element of left subtree in postorder traversal

    int index = 0;
    while (postorder[index] != preorder[preS + 1]) {
        index++;
    }

    // step 5: elements at index before and equal to index are part of left subtree

    int numLeft = index - postS + 1; // this tells the number of left subtree size

    root->left = buildTree(preorder, postorder, preS + 1, preS + numLeft, postS, index);
    // preorder starts from preS + 1 (skipping root) and ends at preS + numLeft (size
    // of left subtree size ahead)
    // post order starts from postS and ends at index (at which first element of left
    // subtree found)

    root->right = buildTree(preorder, postorder, preS + numLeft + 1, preE, index + 1, postE - 1);
    // similar for this, preorder starts from just after where left preorder ends and ends
    // at end of preorder
    // post order starts from just after the index at which first element of left subtree
    // found and ends at just before root at the end.

    return root;
}

TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
    if (preorder.size() == 0 || postorder.size() == 0) {
        return NULL;
    }

    return buildTree(preorder, postorder, 0, preorder.size() - 1, 0, postorder.size() - 1);
}

// Approach 2: Using Recursion with hashmap
// Time Complexity: O(N)
// Space Complexity: O(N)

TreeNode* buildTree(vector<int>& preorder, vector<int>& postorder, int preS, int preE, int postS, int postE, unordered_map<int, int> &postMap) {
    if (preS > preE || postS > postE) {
        return NULL;
    }

    int rootData = preorder[preS];
    TreeNode* root = new TreeNode(rootData);

    if (preS + 1 > preE) {
        return root;
    }

    int index = postMap[preorder[preS + 1]];
    // we use hashmap to find index at which first element of left subtree found

    int numLeft = index - postS + 1;

    root->left = buildTree(preorder, postorder, preS + 1, preS + numLeft, postS, index, postMap);
    // preorder starts from preS + 1 (skipping root) and ends at preS + numLeft (size
    // of left subtree size ahead)
    // post order starts from postS and ends at index (at which first element of left
    // subtree found)
    
    root->right = buildTree(preorder, postorder, preS + numLeft + 1, preE, index + 1, postE - 1, postMap);
    // similar for this, preorder starts from just after where left preorder ends and ends
    // at end of preorder
    // post order starts from just after the index at which first element of left subtree
    // found and ends at just before root at the end.

    return root;
}

TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
    if (preorder.size() == 0 || postorder.size() == 0) {
        return NULL;
    }

    unordered_map<int, int> postMap;

    for (int i=0; i<postorder.size(); i++) {
        postMap[postorder[i]] = i;
    }

    return buildTree(preorder, postorder, 0, preorder.size() - 1, 0, postorder.size() - 1, postMap);
}