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

// Approach 1: Using Mirror Binary Tree method
// Time Complexity: O(N)
// Space Complexity: O(N)

void preOrder(BinaryTreeNode<int> *root, vector<int> &tree) { // pre-order traversal
    if (root == NULL) {
        return;
    }

    tree.push_back(root->data);

    preOrder(root->left, tree);

    preOrder(root->right, tree);
}

void mirrorTree(BinaryTreeNode<int> *root) {
    if (root == NULL) {
        return;
    }

    BinaryTreeNode<int> *temp = root->left; // swap left and right childs
    root->left = root->right;
    root->right = temp;

    mirrorTree(root->left); // mirror left subtree

    mirrorTree(root->right); // mirror right subtree
}

bool isSymmetric(BinaryTreeNode<int>* root) {
    if (root == NULL) {
        return true;
    }

    vector<int> currTree;
    preOrder(root, currTree); // store the tree in currTree in pre-order fashion.

    mirrorTree(root); // now mirror the tree

    vector<int> mirrorTree;
    preOrder(root, mirrorTree); // store the mirrorTree in pre-order fashion.

    if (currTree == mirrorTree) { // now check both pre-order are equal or not
        return true;
    }
    return false;
}

// Approach 2: In-order Traversal and reverse In-order Traversal
// Time Complexity: O(N)
// Space Complexity: O(N)

bool checkSymmetric(BinaryTreeNode<int> *root, BinaryTreeNode<int> *mirrorRoot) {
    // step 1: check is both root and mirror root is null or not

    if (root == NULL && mirrorRoot == NULL) {
        return true;
    }

    // step 2: check is current root is null and mirror root is not null and vice versa
    // if either two is true, then tree is not symmetric 

    if (root == NULL && mirrorRoot != NULL) {
        return false;
    }

    if (root != NULL && mirrorRoot == NULL) {
        return false;
    }

    // step 3: check the data of both root are they equal or not?

    if (root->data != mirrorRoot->data) {
        return false;
    }

    // step 4: now check for both left and right side of both general tree and mirrored
    // tree

    bool leftAns = checkSymmetric(root->left, mirrorRoot->right);

    bool rightAns = checkSymmetric(root->right, mirrorRoot->left);

    return leftAns && rightAns; // if both is symmetric, then return ans
}

bool isSymmetric(BinaryTreeNode<int>* root) {
    return checkSymmetric(root, root);
}