#include <iostream>
using namespace std;

template <typename T>
class BinaryTreeNode {
    public:
    T data;
    BinaryTreeNode<T> *left;
    BinaryTreeNode<T> *right;

    BinaryTreeNode(T data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }

    ~BinaryTreeNode() {
        delete left;
        delete right;
    }
};

/*
Self Notes 📜:
🥥 if both children sum is less than parent, make children's value to parent's value.
🥥 if both children values sum is greater than or equal to parent, make parent's 
   value to children's sum.
🥥 recursively go left and right. Traversal type: DFS.
🥥 when coming back up the tree, take children sum and replace it in parent.
🥥 at any point we reach null, just return (base case)
🥥 Intuition: while going down, increase the children values so we make sure to 
   never fall short, then all we have to do is sum both children and replace it in 
   parent.
*/

// Approach 1: Using Post-Order Traversal 

// Time Complexity: O(N^2)
// Space Complexity: O(N)

void increment(BinaryTreeNode<int>* root, int diff) {
    if (root->right != NULL) { 
        // either increment right to match the parent value

        root->right->data = root->right->data + diff;
        increment(root->right, diff);
    } 
    else if (root -> left != NULL) { 
        // either increment left to match the parent value

        root->left->data = root->left->data + diff;
        increment(root->left, diff);
    }
}

void changeTree(BinaryTreeNode<int>* root) {
    // Base case.
    if (root == NULL || (root -> left == NULL && root -> right == NULL)) {
        return;
    }

    // Traverse substrees.
    changeTree(root->left);
    changeTree(root->right);

    // now find the child sum of root
    int left = 0; int right = 0;
    if (root->left != NULL) {
        left = root->left->data;
    }
    if (root->right != NULL) {
        right = root->right->data;
    }

    // now if child sum is bigger than root->data, change the root data
    if (left + right > root->data) {
        root->data = left + right;
    } 
    else { // if not, increment the left and right subtree with their difference
        int diff = root->data - (left + right);
        increment(root, diff);
    }
}

// Approach 2: Using Post-Order Traversal (optimal)
// Time Complexity: O(N)
// Space Complexity: O(N) {in case of skewed tree}

void changeTree(BinaryTreeNode<int> *root) {
    // step 1: check for base case

    if (root == NULL) {
        return;
    }

    // step 2: take left and right child data if exists

    int left = (root->left == NULL) ? 0 : root->left->data;
    int right = (root->right == NULL) ? 0 : root->right->data;

    // step 3: check is sum of left and right child is greater or equal to root data
    // if yes, update it and if not, make its children data equal to root data

    if (left + right >= root->data) {
        root->data = left + right;
    }
    else {
        if (root->left != NULL) {
            root->left->data = root->data; // make left child data = root data if exists
        }
        if (root->right != NULL) {
            root->right->data = root->data; // make right child data = root data if exists
        }
    }

    // step 4: solve for left subtree and right subtree
    
    changeTree(root->left);
    changeTree(root->right);

    // step 5: after coming back and solving left and right subtree, update the root data
    // to the sum of left and right because maybe left child or right child data can be
    // different from previous data.

    left = (root->left == NULL) ? 0 : root->left->data;
    right = (root->right == NULL) ? 0 : root->right->data;

    if (root->left != NULL || root->right != NULL) { 
        // update only if the root is not leaf node

        root->data = left + right;
    }
}  