#include <iostream>
#include <climits>
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

// Approach 1: Brute Force 
// Time Complexity: O(N^2)
// Space Complexity: O(N)

int getMax(BinaryTreeNode<int> *root) { // find max in the tree
	if (root == NULL) {
		return INT_MIN;
	}

	int leftMax = getMax(root->left);
	int rightMax = getMax(root->right);

	return max(root->data, max(leftMax, rightMax));
}

int getMin(BinaryTreeNode<int> *root) { // find min in tree
	if (root == NULL) {
		return INT_MAX;
	}

	int leftMin = getMin(root->left);
	int rightMin = getMin(root->right);

	return min(root->data, min(leftMin, rightMin));
}

bool isBST(BinaryTreeNode<int> *root) {
	if (root == NULL) {
		return true;
	}

	int leftMax = getMax(root->left); // find the left maximum

	int rightMin = getMin(root->right); // find the right minimum

	return isBST(root->left) && isBST(root->right) && (root->data > leftMax) && (root->data <= rightMin);
    // if left and right subtrees are BST && root's data is smaller than right min && 
    // root's data is bigger than left max, then the given tree is BST
}

// Approach 2: Better Brute Force (find max and min for a tree together)
// Time Complexity: O(N^2)
// Space Complexity: O(N)

pair<int, int> getMaxMin(BinaryTreeNode<int> *root) {
    if (root == NULL) {
        return make_pair(INT_MAX, INT_MIN);
    }

    pair<int, int> leftAns = getMaxMin(root->left);

    pair<int, int> rightAns = getMaxMin(root->right);

    int currMin = min(root->data, min(leftAns.first, rightAns.first));
    int currMax = max(root->data, max(leftAns.second, rightAns.second));

    return make_pair(currMin, currMax);
}

bool isBST(BinaryTreeNode<int> *root) {
    if (root == NULL) {
        return true;
    }

    pair<int, int> leftMaxMin = getMaxMin(root->left);
    int leftMax = leftMaxMin.second;

    pair<int, int> rightMaxMin = getMaxMin(root->right);
    int rightMin = rightMaxMin.first;

	return isBST(root->left) && isBST(root->right) && (root->data > leftMax) && (root->data <= rightMin);
}

// Approach 3: Optimal Approach (find all three together)
// Time Compleixty: O(N)
// Space Complexity: O(N)

pair<pair<int,int>, bool> helper(BinaryTreeNode<int> *root) {
    if (root==NULL) {
        return {{INT_MAX, INT_MIN}, true};
        // return make_pair(make_pair(INT_MAX, INT_MIN), true);
    }
    pair<pair<int,int>, bool> leftAns = helper(root->left);
    int leftMin = leftAns.first.first;
    int leftMax = leftAns.first.second;
    bool isleftBST = leftAns.second;

    pair<pair<int,int>, bool> rightAns = helper(root->right);
    int rightMin = rightAns.first.first;
    int rightMax = rightAns.first.second;
    bool isRightBST = rightAns.second;

    int currMin = min(root->data, min(leftMin, rightMin));
    int currMax = max(root->data, max(leftMax, rightMax));
    bool currIsBST = isleftBST && isRightBST && (root->data > leftMax) && (root->data <= rightMin);

    return {{currMin, currMax}, currIsBST};
}

bool isBST(BinaryTreeNode<int> *root) {
    pair<pair<int,int>, bool> output = helper(root);
    return output.second;
}

// Approach 4: Pre-order Traversal
// Time Complexity: O(N)
// Space Complexity: O(N)

bool isBST(BinaryTreeNode<int> *root, int min, int max) {
    if (root == NULL) {
        return true;
    }
    if (root->data > max || root->data < min) { 
        // if root data is less than min & greater than max, root is out of bounds
        return false;
    }

    bool leftHalf = isBST(root->left, min, root->data-1); 
    // check for left subtree max value can be root->data-1 (less than root->data)

    bool rightHalf = isBST(root->right, root->data, max); 
    // check for right subtree minimum value can be root->data (included)

    return leftHalf && rightHalf;
}

bool validateBST(BinaryTreeNode<int> *root) {
    return isBST(root, INT_MIN, INT_MAX);
}

// In-Order Traversal of Binary Tree

// Time Complexity: O(N)
// Space Complexity: O(N)

bool isBST(BinaryTreeNode<int> *root, BinaryTreeNode<int>* &prev) {
    if (root == NULL) {
        return true;
    }

    // check for left subtree in in-order traversal
    if (isBST(root->left, prev) == false) {
        return false;
    }

    // if left subtree is bst, then check for root
    if (prev != NULL && root->data < prev->data) {
        return false;
    }

    prev = root;
    // mark the prev as root for checking right subtree

    // now check for right subtree, after all checking for left & root
    // if right subtree is false, then answer is false and vice-versa
    
    return isBST(root->right, prev);
}

bool validateBST(BinaryTreeNode<int> *root) {
    BinaryTreeNode<int> *prev = NULL;
    return isBST(root, prev);
}