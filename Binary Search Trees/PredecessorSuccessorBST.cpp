#include <iostream>
#include <vector>
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

// Approach 1: Using Inorder-traversal on BST
// Time Complexity: O(N)
// Space Complexity: O(N)

void inorderTraversal(TreeNode *root, vector<int> &inorder) {
    if (root == NULL) {
        return;
    }

    inorderTraversal(root->left, inorder);

    inorder.push_back(root->data);

    inorderTraversal(root->right, inorder);
}

pair<int, int> predecessorSuccessor(TreeNode *root, int key) {
    if (root == NULL) {
        return {-1, -1};
    }

    // step 1: convert the tree into inorder array
    vector<int> inorder;

    inorderTraversal(root, inorder);

    // step 2: now search for predecessor and successor

    int predecessor = -1;
    int successor = -1;

    // left to right loop to find closest smaller to key element
    for (int i = 0; i < inorder.size(); i++) { 
        if (inorder[i] < key) {
            predecessor = inorder[i];
        }
    }

    // right to left loop to find closest bigger than key element
    for (int i = inorder.size() - 1; i >= 0; i--) {
        if (inorder[i] > key) {
            successor = inorder[i];
        }
    }

    // step 3: return predecessor and successor as pair

    return {predecessor, successor};
}

// Approach 2: Using Binary Search instead of Linear Search
// Time Complexity: O(N)
// Space Complexity: O(N)

int predecessor(vector<int> &arr, int key) {
    int start = 0;
    int end = arr.size() - 1;

    int ans = -1;

    while (start <= end) {
        int mid = start + (end - start)/2;

        if (arr[mid] < key) { // if found predecesor, search in more bigger in right
            ans = arr[mid];
            start = mid + 1;
        }
        else {
            end = mid - 1;
        }
    }

    return ans;
}

int successor(vector<int> &arr, int key) {
    int start = 0;
    int end = arr.size() - 1;

    int ans = -1;

    while (start <= end) {
        int mid = start + (end - start)/2;

        if (arr[mid] > key) { // if found successor, search in left half for smaller
            ans = arr[mid];
            end = mid - 1;
        }
        else {
            start = mid + 1;
        }
    }

    return ans;
}

pair<int, int> predecessorSuccessor(TreeNode *root, int key) {
    if (root == NULL) {
        return {-1, -1};
    }

    // step 1: convert the tree into inorder array
    vector<int> inorder;

    inorderTraversal(root, inorder);

    // step 2: now search for predecessor and successor

    int pre = predecessor(inorder, key);
    int suc = successor(inorder, key);

    // step 3: return predecessor and successor as pair

    return {pre, suc};
}

// Approach 3: Optimal Approach (traverse on BST itself instead of inorder array)
// Time Complexity: O(N)
// Space Complexity: O(N)

pair<int, int> predecessorSuccessor(TreeNode *root, int key) {
    if (root == NULL) {
        return {-1, -1};
    }

    // step 1: make the variables to be returned

    int predecessor = -1;
    int successor = -1;

    TreeNode *temp = root;

    // step 2: find predecessor using binary search in BST

    while (temp != NULL) {
        if (temp->data < key) {
            predecessor = temp->data;
            temp = temp->right;
        }
        else {
            temp = temp->left;
        }
    }

    // step 3: find successor using binary search in BST

    temp = root;

    while (temp != NULL) {
        if (temp->data > key) {
            successor = temp->data;
            temp = temp->left;
        }
        else {
            temp = temp->right;
        }
    }

    // step 4: return the answer as pair

    return {predecessor, successor};
}