#include <iostream>
using namespace std;

template <typename T> 
class TreeNode { 
    public: 
    T val; 
    TreeNode<T> *left; 
    TreeNode<T> *right; 
    TreeNode(T val) { 
        this->val = val; 
        left = NULL; 
        right = NULL; 
    } 
};

// Approach 1: Recursive Method for BST
// Time Complexity: O(N)
// Space Complexity: O(N)

class BST {
    // this function returns the root of the binary search tree after insertion.
    TreeNode<int> *insertHelper(TreeNode<int> *node, int value) {
        if (node == NULL) {
            TreeNode<int> *newNode = new TreeNode<int>(value);
            return newNode;
        }

        if (value < node->val) {
            node->left = insertHelper(node->left, value);
        }
        else {
            node->right = insertHelper(node->right, value);
        }

        return node;
    }

    public: 
    TreeNode<int> *root;

    BST() {
        root = NULL;
    }

    void insert(int value) {
        root = insertHelper(root, value); // function to insert value in BST
    }

};

// this helper function inserts the arr values in BST using Binary Search Algorithm
void helper(BST *bst, vector<int> &arr, int start, int end) {
    // step 1: check for base
    if (start > end) {
        return;
    }

    // step 2: find the middle index of arr and insert the middle element in BST

    int mid = start + (end - start)/2;

    bst->insert(arr[mid]);

    // step 3: now call for remaining both left and right halves inserting in same way.

    helper(bst, arr, start, mid-1);

    helper(bst, arr, mid+1, end);
}

TreeNode<int>* sortedArrToBST(vector<int> &arr, int n) {
    BST *bst = new BST(); // BST class object for inserting elements in BST

    helper(bst, arr, 0, n-1); // call function to insert all values

    return bst->root; // finally return the BST root.
}

// Approach 2: Recursive Approach without using BST class
// Time Complexity: O(N)
// Space Complexity: O(N)

TreeNode<int>* convertArrToBST(vector<int> &arr, int start, int end) {
    // step 1: base case
    if (start > end) {
        return NULL;
    }

    // step 2: find mid of the arr and insert it into the BST

    int mid = start + (end - start)/2;

    TreeNode<int> *newNode = new TreeNode<int>(arr[mid]);

    // step 3: convert remaining array and insert them into left and right of newNode

    newNode->left = convertArrToBST(arr, start, mid-1);

    newNode->right = convertArrToBST(arr, mid+1, end);

    // step 4: finally return the newNode which is root of the binary search tree

    return newNode;
}

TreeNode<int>* sortedArrToBST(vector<int> &arr, int n) {
    TreeNode<int> *root = convertArrToBST(arr, 0, n-1);

    return root;
}

// Approach 3: Iterative Approach for inserting element in BST.
// Time Complexity: O(N)
// Space Complexity: O(N)

class BST {
    public: 
    TreeNode<int> *root;

    BST() {
        root = NULL;
    }

    // this function inserts value in BST iteratively
    void insert(int value) {
        TreeNode<int> *newNode = new TreeNode<int>(value);
        if (root == NULL) { // if root is NULL, insert newNode at root
            root = newNode;
            return;
        }

        TreeNode<int> *prev = NULL;
        TreeNode<int> *temp = root;

        while (temp != NULL) { 
            // traverse the tree from root to the leaf node where we have to insert
            // our newNode

            if (value < temp->val) {
                prev = temp;
                temp = temp->left;
            }
            else {
                prev = temp;
                temp = temp->right;
            }
        }

        // now compare the leaf node's data with value, if small insert in left
        // else in right

        if (value < prev->val) { 
            prev->left = newNode;
        }
        else {
            prev->right = newNode;
        }
    }
};

// this helper function inserts the arr values in BST using Binary Search Algorithm
void helper(BST *bst, vector<int> &arr, int start, int end) {
    // step 1: check for base
    if (start > end) {
        return;
    }

    // step 2: find the middle index of arr and insert the middle element in BST

    int mid = start + (end - start)/2;

    bst->insert(arr[mid]);

    // step 3: now call for remaining both left and right halves inserting in same way.

    helper(bst, arr, start, mid-1);

    helper(bst, arr, mid+1, end);
}

TreeNode<int>* sortedArrToBST(vector<int> &arr, int n) {
    BST *bst = new BST(); // BST class object for inserting elements in BST

    helper(bst, arr, 0, n-1); // call function to insert all values

    return bst->root; // finally return the BST root.
}