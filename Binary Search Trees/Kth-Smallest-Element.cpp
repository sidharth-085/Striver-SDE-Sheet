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

// Approach 1: Using Recursion with extra array
// Time Complexity: O(N)
// Space Complexity: O(N)

void inorder(TreeNode<int> *root, vector<int> &ans) {
    if (root == NULL) {
        return;
    }

    inorder(root->left, ans);

    ans.push_back(root->data);

    inorder(root->right, ans);
}

int kthSmallest(TreeNode<int> *root, int k) {
    if (root == NULL) {
        return NULL;
    }

    vector<int> ans;
    inorder(root, ans);
    
    return ans[k-1];
}

// Approach 2: Inorder-Traversal without Extra array
// Time Complexity: O(N)
// Space Complexity: O(N)

int inorder(TreeNode<int> *root, int k, int &count) {
    // step 1: base case if root is null
    if (root == NULL) {
        return -1;
    }

    // step 2: for smallest element, it should be on left side of root

    int left = inorder(root->left, k, count);

    if (left != -1) { // if left subtree have kth smallest element
        return left;
    }

    // step 3: include the current root element and check is the count is equal to k

    count++;

    if (count == k) { // if count == k, means we have found our kth element at root
        return root->data;
    }

    // step 4: if count is not equal to k, it means we haven't found kth snallest
    // and try on right subtree. If we didn't found, return -1.

    return inorder(root->right, k, count);
}

int kthSmallest(TreeNode<int> *root, int k) {
    int count = 0;

    return inorder(root, k, count); // function call
}