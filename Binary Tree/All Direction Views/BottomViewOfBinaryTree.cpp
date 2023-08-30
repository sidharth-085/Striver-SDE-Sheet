#include <iostream>
#include <queue>
#include <map>
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
};

// Approach 1: Using Pre-Order Traversal

// Time Complexity: O(N*Log N)
// Space Complexity: O(N)

void preOrder(TreeNode<int> *root, map<int, pair<int, int>> &visited, int hDistance, int level) {
    // step 1: check for base case
    
    if (root == NULL) {
        return;
    }

    // step 2: check is the current hDistance already exists in map or not, if not
    // add the node and level of the node in map. If it already exists, check the current
    // level should be equal or greater than previous stored level to give proper bottom
    // view

    map<int, pair<int, int>>::iterator it = visited.find(hDistance);

    if (it == visited.end() || (it->second).second <= level) {  // Change < to <=
        visited[hDistance] = {root->data, level};
    }

    // step 3: now just call on left side && right side with updated hDistance and level

    preOrder(root->left, visited, hDistance - 1, level + 1);

    preOrder(root->right, visited, hDistance + 1, level + 1);
}

vector<int> bottomView(TreeNode<int> * root) {
    vector<int> ans;
    
    if (root == NULL) {
        return ans;
    }

    map<int, pair<int, int>> visited;

    preOrder(root, visited, 0, 0); 
    // visited map will store all the values of bottom view nodes

    for (auto it : visited) {
        ans.push_back(it.second.first); // copy it in ans and return
    }

    return ans;
}

// Approach 2: Using Level-Order Traversal

// Time Complexity: O(N*Log N)
// Space Complexity: O(N)

void levelOrder(TreeNode<int> * root, map<int, pair<int,int>> &visited) {
    // step 1: check for edge case 

    if (root == NULL) {
        return;
    }

    // step 2: make a queue and push the current root with hDistance and level

    queue<pair<int, pair<TreeNode<int>*, int>>> q;
    q.push({0, {root, 0}});

    while (!q.empty()) {
        // take out the current node and pop it from queue
        pair<int, pair<TreeNode<int>*, int>> front = q.front();
        q.pop();

        // store their values in separate variables
        int hDistance = front.first;
        TreeNode<int> *node = front.second.first;
        int level = front.second.second;

        map<int, pair<int,int>>::iterator it = visited.find(hDistance);
        // check is the current hDistance have some node with it in map.
        // If not, update the current node with its data and level
        // If yes, check the current level should be more than previously stored level

        if (it == visited.end() || (it->second).second <= level) {
            visited[hDistance] = {node->data, level};
        }

        // step 3: now just store the left and right nodes with updated horizontal 
        // distances and level

        if (node->left != NULL) {
            q.push({hDistance - 1, {node->left, level + 1}});
        }

        if (node->right != NULL) {
            q.push({hDistance + 1, {node->right, level + 1}});
        }
    }
}

vector<int> bottomView(TreeNode<int> * root) {
    vector<int> ans;
    
    if (root == NULL) {
        return ans;
    }

    map<int, pair<int, int>> visited;

    levelOrder(root, visited); 
    // visited map will store all the values of bottom view nodes

    for (auto it : visited) {
        ans.push_back(it.second.first); // copy it in ans and return
    }

    return ans;
}
