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
};

// Diameter of binary tree is the longest distance from any two nodes and distance can
// be seen as height from particular two nodes

// Approach 1: Brute Force Solution
// Time Complexity: O(N^2)
// Space Complexity: O(N)

// function for finding the height of the binary tree
int getHeight(TreeNode<int> *root) { 
    if (root == NULL) {
        return 0;
    }

    int leftHeight = getHeight(root->left);

    int rightHeight = getHeight(root->right);

    return max(leftHeight, rightHeight) + 1;
}

void diameterOfBinaryTree(TreeNode<int> *root, int &diameter) {
    // step 1: check for base case
    if (root == NULL) {
        return;
    }   

    // step 2: find the left and right height for every node

    int leftHeight = getHeight(root->left);

    int rightHeight = getHeight(root->right);

    // step 3: maximize the diameter by adding the left height and right height

    diameter = max(diameter, leftHeight + rightHeight);

    // step 4: call on left and right side to get the answer for every node

    diameterOfBinaryTree(root->left, diameter);
    diameterOfBinaryTree(root->right, diameter);
}

int diameterOfBinaryTree(TreeNode<int> *root) {
    int diameter = 0;
    
    diameterOfBinaryTree(root, diameter);

    return diameter;
}

// Approach 2: Similar to above approach with same complexity
// Time Complexity: O(N^2)
// Space Complexity: O(N)

int diameterOfBinaryTree(TreeNode<int> *root) {
    if (root == NULL) {
        return 0;
    }

    int option1 = getHeight(root->left) + getHeight(root->right);
    // this option 1 gets the possible case 1 if current node itself have the diameter

    int option2 = diameterOfBinaryTree(root->left);
    // this option 2 gets, there can be diameter present in left

    int option3 = diameterOfBinaryTree(root->right);
    // this option 3 gets, there can be diameter present in right

    return max(option1, max(option2, option3)); // the maximum of it, is the diameter
}

// Approach 3: Optimal Approach
// Time Complexity: O(N)
// Space Complexity: O(N)

// use the height function just add the condition for diameter because we already have 
// left and right height in finding the height function

int heightDiameter(TreeNode<int> *root, int &diameter) {
    if (root == NULL) {
        return 0;
    }

    int leftHeight = heightDiameter(root->left, diameter); 
    // it finds the left height

    int rightHeight = heightDiameter(root->right, diameter); 
    // it finds the right height

    diameter = max(diameter, leftHeight + rightHeight); 
    // diameter updates with (leftHeight + rightHeight)

    return max(leftHeight, rightHeight) + 1; // it usually returns the height
}

int diameterOfBinaryTree(TreeNode<int> *root) {
    int diameter = 0;

    heightDiameter(root, diameter);

    return diameter;
}

// Approach 4: Similar to above one, instead of finding the left and right heights 
// find it together

// Time Complexity: O(N)
// Space Complexity: O(N)

// this function contains both height && diameter 

class Info {
    public: 
    int height;
    int diameter;
};

Info heightDiameter(TreeNode<int> *root) { 
    // step 1: base case
    if (root == NULL) {
        return {0, 0}; 
    }

    // step 2: find height and diameter of left side and right side

    Info leftSide = heightDiameter(root->left);
    Info rightSide = heightDiameter(root->right);

    // step 3: now check height and diameter for current node 

    int currHeight = max(leftSide.height, rightSide.height) + 1;
    int diameter = max((leftSide.height + rightSide.height), max(leftSide.diameter, rightSide.diameter));

    return {currHeight, diameter};
}

int diameterOfBinaryTree(TreeNode<int> *root) {
    Info ans = heightDiameter(root);

    return ans.diameter;
}