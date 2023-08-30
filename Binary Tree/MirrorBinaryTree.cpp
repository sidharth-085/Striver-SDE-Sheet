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

// Approach: General Approach Post Order, mirror the left and right subtrees and then 
// swap left child and right child of root

// Time Complexity: O(N)
// Space Complexity: O(N)

void mirrorBinaryTree(BinaryTreeNode<int>* root) {
	if (root == NULL) {
		return;
	}

	mirrorBinaryTree(root->left); // mirror left subtree

	mirrorBinaryTree(root->right); // mirror right subtree

	BinaryTreeNode<int> *node = root->left; // swap left and right childs of root
	root->left = root->right;
	root->right = node;
}

// Approach: Pre-order Traversal

// Time Complexity: O(N)
// Space Complexity: O(N)

void mirrorBinaryTree(BinaryTreeNode<int>* root) {
	if (root == NULL) {
		return;
	}

    BinaryTreeNode<int> *node = root->left; // swap left and right childs of root
	root->left = root->right;
	root->right = node;

	mirrorBinaryTree(root->left); // mirror left subtree

	mirrorBinaryTree(root->right); // mirror right subtree
}