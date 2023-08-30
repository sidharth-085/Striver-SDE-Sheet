#include <iostream>
#include <vector>
#include <map>
#include <queue>
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

// Approach 1: Pre-order traversal

// Time Complexity: O(N*LogN) {Log N due to inserting of element in map}
// Space Complexity: O(N)

void preOrder(TreeNode<int> *root, map<int, pair<int, int>> &visited, int hDistance, int level) {
    // step 1: check for base case

    if (root == NULL) {
        return;
    }

    // step 2: check is current horizontal distance exists in visited i.e. this distance
    // already visited or if it is visited, check the level of the node, if the current
    // level is bigger than the previously stored level, it means the current node is
    // hidden by previously stored node, so dont put in map.

    map<int, pair<int, int>>::iterator it = visited.find(hDistance);

    if (it == visited.end() || (it->second).second > level) {
        visited[hDistance] = {root->data, level};
    }

    // step 3: now check for left and right subtrees

    preOrder(root->left, visited, hDistance - 1, level + 1);
    // when we are moving in left direction, we will go in negative direction so 
    // hDistance - 1, will be the next horizontal distance.

    preOrder(root->right, visited, hDistance + 1, level + 1);
    // when we are moving in right direction, we will go in positive direction so 
    // hDistance - 1, will be the next horizontal distance.
}

vector<int> getTopView(TreeNode<int> *root) {
    vector<int> ans;

    // step 1: check for edge case, is root is null or not

    if (root == NULL) {
        return ans;
    }

    // step 2: make a map to store the the visited horizontal distances as key
    // and value of the node and the level as pair.

    map<int, pair<int, int>> visited;

    // step 3: now call for pre-order traveral to store the all elements in visited
    // map.

    preOrder(root, visited, 0, 0);

    // step 4: after that copy the elements of map in ans vector

    for (auto it : visited) {
        ans.push_back(it.second.first);
    } 

    return ans;
}

// Approach 2: Level-order Traversal 

// Time Complexity: O(N*Log N)
// Space Complexity: O(N)

void levelOrder(TreeNode<int> *root, map<int, pair<int, int>> &visited) {
    // step 1: check for edge case is root is null or not

    if (root == NULL) {
        return;
    }

    // step 2: for level order traversal we need a queue which stores horizontal 
    // distance node value and level of the node

    queue<pair<int, pair<TreeNode<int>*, int>>> q;

    q.push({0, {root, 0}}); // root has horizontal distance as 0 && level 0.

    while (!q.empty()) {
        pair<int, pair<TreeNode<int>*, int>> front = q.front(); // take out from queue
        q.pop();

        // value of the node put out from queue
        int hDistance = front.first; 
        TreeNode<int> *node = front.second.first;
        int level = front.second.second;

        map<int, pair<int, int>>::iterator it = visited.find(hDistance);

        // check is current horizontal distance exists in visited i.e. this distance 
        // already visited or if it is visited, check the level of the node, if the 
        // current level is bigger than the previously stored level, it means the 
        // current node is hidden by previously stored node, so dont put in map.
    
        if (it == visited.end() || (it->second).second > level) {
            visited[hDistance] = {node->data, level};
        }

        if (node->left != NULL) {
            q.push({hDistance - 1, {node->left, level + 1}});
            // now for left, insert it with new values of hDistance and level
        }

        if (node->right != NULL) {
            q.push({hDistance + 1, {node->right, level + 1}});
            // now for right, insert it with new values of hDistance and level
        }
    }
}

vector<int> getTopView(TreeNode<int> *root) {
    vector<int> ans;

    // step 1: check for edge case, is root is null or not

    if (root == NULL) {
        return ans;
    }

    // step 2: make a map to store the the visited horizontal distances as key
    // and value of the node and the level as pair.

    map<int, pair<int, int>> visited;

    // step 3: now call for level-order traveral to store the all elements in visited
    // map.

    levelOrder(root, visited);

    // step 4: after that copy the elements of map in ans vector

    for (auto it : visited) {
        ans.push_back(it.second.first);
    } 

    return ans;
}