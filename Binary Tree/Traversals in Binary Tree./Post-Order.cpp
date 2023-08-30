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

void postOrder(TreeNode *root, vector<int> &ans) {
    if (root == NULL) {
        return;
    }

    postOrder(root->left, ans); // work on left

    postOrder(root->right, ans); // work on right

    ans.push_back(root->data); // work on root
}

vector<int> getPostOrderTraversal(TreeNode *root) {
    vector<int> ans;

    if (root == NULL) {
        return ans;
    }

    postOrder(root, ans); // call for post order traversal

    return ans;
}