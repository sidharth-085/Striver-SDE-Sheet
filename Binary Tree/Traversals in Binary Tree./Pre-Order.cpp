#include <iostream>
using namespace std;

class TreeNode {
    public:
    
    int data;
    TreeNode *left, *right;
    TreeNode() : data(0), left(NULL), right(NULL) {}
    TreeNode(int x) : data(x), left(NULL), right(NULL) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : data(x), left(left), right(right) {}
};

// Time Complexity: O(N)
// Space Complexity: O(N)

// Pre-order / Post-order / In-Order traversals is similar to DFS algortithm of Graphs

void preOrder(TreeNode* root, vector<int> &ans) {
    if (root == NULL) {
        return;
    }

    ans.push_back(root->data); // add the root in ans

    preOrder(root->left, ans); // work on left

    preOrder(root->right, ans); // work on right
}

vector<int> getPreOrderTraversal(TreeNode *root) {
    vector<int> ans;

    if (root == NULL) {
        return ans;
    }

    preOrder(root, ans); // call pre-order

    return ans;
}