#include <iostream>
#include <vector>
#include <climits>
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

// Approach 1: Using Recursion
// Time Complexity: O(N^2)
// Space Complexity: O(N)

TreeNode *buildTree(vector<int> &preorder, int preS, int preE) {
    // step 1: check for base case

    if (preS > preE) {
        return NULL;
    }

    // step 2: make root from first element in preorder

    int rootData = preorder[preS];
    TreeNode *root = new TreeNode(rootData);

    // step 3: start from first element of preorder & go till the element which is 
    // bigger than root value

    int index = preS + 1;

    while (index <= preE && preorder[index] < rootData) {
        index++;
    }

    // step 4: now we get the element which is bigger than root. Now, build tree for
    // left and right subtree.

    root->left = buildTree(preorder, preS + 1, index - 1);
    // left subtree starts from next element of root and goes till before large element
    // than root value

    root->right = buildTree(preorder, index, preE);
    // right subtree starts from index (large element than root value) till end.

    return root;
}

TreeNode *preOrderTree(vector<int> &preorder) {
    return buildTree(preorder, 0, preorder.size() - 1);
}

// Approach 2: Optimized Approach
// Time Complexity: O(N)
// Space Complexity: O(N)

TreeNode *buildTree(vector<int> &preorder, int &preIndex, int startRange, int endRange) {
    if (preIndex >= preorder.size()) {
        return NULL;
    }

    int currNode = preorder[preIndex];

    if (currNode > startRange && currNode < endRange) {
        TreeNode *root = new TreeNode(currNode);

        preIndex++;

        if (preIndex < preorder.size()) {
            root->left = buildTree(preorder, preIndex, startRange, currNode);
        }

        if (preIndex < preorder.size()) {
            root->right = buildTree(preorder, preIndex, currNode, endRange);
        }

        return root;
    }

    return NULL;
}

TreeNode *preOrderTree(vector<int> &preorder) {
    int preIndex = 0;

    return buildTree(preorder, preIndex, INT_MIN, INT_MAX);
}