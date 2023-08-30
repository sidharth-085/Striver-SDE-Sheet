#include <iostream>
#include <vector>
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

// Approach 1: Using vector pointer
// Time Complexity: O(N)
// Space Complexity: O(N)

vector<int>* longestPathFromLeafToRoot(TreeNode<int> *root) {
    // If the current node is NULL, return NULL indicating an empty path

    if (root == NULL) {
        return NULL;
    }

    // Create a vector to store the longest path from leaf to root

    vector<int>* longestPath = new vector<int>();

    // If the current node is a leaf (no children), add its value to the path

    if (root->left == NULL && root->right == NULL) {
        longestPath->push_back(root->data);
        return longestPath;
    }

    // Recursively find the longest paths from leaf to root for the left and right

    vector<int>* left = longestPathFromLeafToRoot(root->left);
    vector<int>* right = longestPathFromLeafToRoot(root->right);

    // If the left path is NULL (no left subtree), update the path with the right 
    // subtree

    if (left == NULL) {
        right->push_back(root->data);
        longestPath = right;
    }

    // If the right path is NULL (no right subtree), update the path with the left 
    // subtree

    else if (right == NULL) {
        left->push_back(root->data);
        longestPath = left;
    }

    // If both left and right paths exist, choose the longer path

    else {
        if (left->size() >= right->size()) {
            left->push_back(root->data);
            longestPath = left;
        } 
        else {
            right->push_back(root->data);
            longestPath = right;
        }
    }

    return longestPath;
}


// Approach 2: Path traversal with vector pointer
// Time Complexity: O(N)
// Space Complexity: O(N)

vector<int> longestPathFromLToR(TreeNode<int> *root) {
    vector<int> longestPath;

    if (root == NULL) {
        return longestPath; // Return an empty vector for NULL nodes
    }

    if (root->left == NULL && root->right == NULL) {
        longestPath.push_back(root->data);
        return longestPath; // Return a vector with the leaf node's data
    }

    vector<int> left = longestPathFromLToR(root->left);
    vector<int> right = longestPathFromLToR(root->right);

    // Compare the lengths of left and right paths
    if (left.size() >= right.size()) {
        longestPath = left; // Update longestPath with the left path
    } 
    else {
        longestPath = right; // Update longestPath with the right path
    }

    longestPath.push_back(root->data); // Add the current node's data

    return longestPath;
}