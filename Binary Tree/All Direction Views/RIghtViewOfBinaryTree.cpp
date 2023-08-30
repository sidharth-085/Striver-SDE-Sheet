#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

class TreeNode {
    public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Approach 1: Using Recursion with map (DFS)
// Time Complexity: O(N)
// Space Complexity: O(N)

void rightSideViewHelper(TreeNode* root, map<int, int> &visited, int level) {
    if (root == NULL) {
        return;
    }

    if (visited.find(level) == visited.end()) {
        visited[level] = root->val;
    }

    rightSideViewHelper(root->right, visited, level + 1);

    rightSideViewHelper(root->left, visited, level + 1);
}

vector<int> rightSideView(TreeNode* root) {
    vector<int> ans;
    if (root == NULL) {
        return ans;
    }

    map<int, int> visited;

    rightSideViewHelper(root, visited, 0);

    for (auto &it : visited) {
        ans.push_back(it.second);
    }

    return ans;
}

// Approach 2: Using Recursion without map (DFS)
// Time Complexity: O(N)
// Space Complexity: O(N)

void rightSideViewHelper(TreeNode* root, vector<int> &ans, int &maxLevel, int level) {
    if (root == NULL) {
        return;
    }

    if (level > maxLevel) {
        ans.push_back(root->val);
        maxLevel = level;
    }

    rightSideViewHelper(root->right, ans, maxLevel, level + 1);

    rightSideViewHelper(root->left, ans, maxLevel, level + 1);
}

vector<int> rightSideView(TreeNode* root) {
    vector<int> ans;
    if (root == NULL) {
        return ans;
    }

    int maxLevel = -1;
    rightSideViewHelper(root, ans, maxLevel, 0);

    return ans;
}

// Approach 3: Using Level Order Traversal (BFS) without map
// Time Complexity: O(N)
// Space Complexity: O(N)

vector<int> rightSideView(TreeNode* root) {
    vector<int> ans;
    if (root == NULL) {
        return ans;
    }

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();

        for (int i=0; i<size; i++) {
            TreeNode *node = q.front();
            q.pop();

            if (i == size-1) {
                ans.push_back(node->val);
            }

            if (node->left) {
                q.push(node->left);
            }

            if (node->right) {
                q.push(node->right);
            }
        }
    }

    return ans;
}