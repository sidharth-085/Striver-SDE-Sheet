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

// Approach 1: Inorder-Traversal 
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

int kthLargestNumber(TreeNode<int>* root, int k)  {
    vector<int> ans;

    inorder(root, ans);

    int size = ans.size();

    // if k is bigger than tree size, then return -1

    if (size < k) {
        return -1;
    }

    return ans[size - k]; // kth largest number 
}

// Approach 2: Using Reverse-inorder Traversal
// Time Complexity: O(N)
// Space Complexity: O(N)

int revInorder(TreeNode<int> *root, int k, int &count) {
    // step 1: base case if root is NULL
    if (root == NULL) {
        return -1;
    }

    // step 2: check in right subtree because kth largest element should be on right
    // subtree of root

    int right = revInorder(root->right, k, count);

    if (right != -1) { // if found the element, return the answer
        return right;
    }

    // step 3: if we dont found the kth largest element in right half, add the root
    // in the count

    count++;

    // if we reached to the k, counts return root->data because last node which is 
    // added to make count equal to k, is root node

    if (count == k) { 
        return root->data;
    }

    // step 4: finally, if count is not equal to k and we haven't find the kth largest
    // element. If not found, return -1.

    return revInorder(root->left, k, count);
}

int kthLargestNumber(TreeNode<int>* root, int k)  {
    int count = 0;

    return revInorder(root, k, count);
}