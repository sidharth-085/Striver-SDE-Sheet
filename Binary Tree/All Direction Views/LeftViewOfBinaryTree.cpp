#include <iostream>
#include <vector>
#include <queue>
#include <map>
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

// Approach 1: Pre-order traversal with Map
// Time Complexity: O(N)
// Space Complexity: O(N)

void getLeftViewHelper(TreeNode<int> *root, map<int, int> &visited, int level) {
    // step 1: check for base case
    if (root == NULL) {
        return;
    }

    // step 2: check is current level exists in map already or not, we traversed left 
    // first so if again the level comes we dont have to take it 

    if (visited.find(level) == visited.end()) {
        visited[level] = root->data;
    }

    // step 3: call for left side and right side 

    getLeftViewHelper(root->left, visited, level + 1); 

    getLeftViewHelper(root->right, visited, level + 1);
}

vector<int> getLeftView(TreeNode<int> *root) {
    vector<int> ans;

    if (root == NULL) {
        return ans;
    }

    map<int, int> visited; // map for keep the track of level with its left view value

    getLeftViewHelper(root, visited, 0);

    for (auto &it : visited) { // copy the map values to ans
        ans.push_back(it.second);
    }

    return ans;
}

// Approach 2: Pre-order traversal without map
// Time Complexity: O(N)
// Space Complexity: O(N)

// Function for doing preorder traversal of a binary tree.
void preorderTraversal(TreeNode<int> *root, int level, int &maxLevel, vector<int> &leftView) {
    if (root == NULL) {
        return;
    }

    // If the current level is greater than the maxlevel then store the current node.
    // if we come back of same level at which we already taken node, the level of that
    // node will always be less than max level at which we have visited already

    if (level > maxLevel) {
        leftView.push_back(root->data);
        maxLevel = level;
    }

    // Recur for the left subtree.
    preorderTraversal(root->left, level + 1, maxLevel, leftView);

    // Recur for the right subtree.
    preorderTraversal(root->right, level + 1, maxLevel, leftView);
}

vector<int> getLeftView(TreeNode<int> *root) {   
    // For storing the left view of the binary tree.
    vector<int> leftView;

    int maxLevel = -1;

    // Do a preorder traversal of the binary tree.
    preorderTraversal(root, 0, maxLevel, leftView);

    // Return the left view of the binary tree.
    return leftView;
}

// Approach 3: Level order traversal with Map
// Time Complexity: O(N)
// Space Complexity: O(N)

vector<int> getLeftView(TreeNode<int> *root) {
    vector<int> ans;

    if (root == NULL) {
        return ans;
    }

    map<int, int> visited;

    queue<pair<TreeNode<int>*, int>> q;
    q.push({root, 0});

    while (!q.empty()) {
        pair<TreeNode<int>*, int> front = q.front();
        q.pop();

        TreeNode<int> *node = front.first;
        int level = front.second;

        if (visited.find(level) == visited.end()) {
            visited[level] = node->data;
        }

        if (node->left != NULL) {
            q.push({node->left, level + 1});
        }

        if (node->right != NULL) {
            q.push({node->right, level + 1});
        }
    }

    for (auto &it : visited) {
        ans.push_back(it.second);
    }

    return ans;
}

// Approach 4: Level order traversal without map
// Time Complexity: O(N)
// Space Complexity: O(N)

vector<int> getLeftView(TreeNode<int> *root) {
    // For storing the left view.
    vector<int> leftView;

    if (root == NULL) {
        return leftView;
    }

    // Queue for doing level order traversal (it stores all nodes at particular level)
    queue<TreeNode<int>*> level;

    // Push the root in the queue.
    level.push(root);
    int leftMostNode = -1;

    while (!level.empty()) {
        
        // Get the size of the current level.
        int queueSize = level.size();

        // Traverse all nodes of the current level.
        for (int i = 0; i < queueSize; i++) {
            
            // Pop the node from the front of the queue.
            TreeNode<int> *curr = level.front();
            level.pop();

            // Store the left most node of the current level.
            if (i == 0) {
                leftMostNode = curr->data;
            }

            // Push the left child into the queue.
            if (curr->left != NULL) {
                level.push(curr->left);
            }

            // Push the right child into the queue.
            if (curr->right != NULL) {
                level.push(curr->right);
            }
        }

        //    Store the left most node of the current level in the array.
        leftView.push_back(leftMostNode);
    }

    //    Return the left view of the given binary tree.
    return leftView;
}