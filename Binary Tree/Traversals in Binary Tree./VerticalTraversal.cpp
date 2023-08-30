#include <iostream>
#include <map>
#include <queue>
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

// Approach using Level Order Traversal
// Time Complexity: O(N)
// Space Complexity: O(N)

// Class which stores node with its horizontal distance from root and its level
// for location
class Node {
    public:
    TreeNode<int> *node;
    int hDistance;
    int level;
};

vector<int> verticalOrderTraversal(TreeNode<int> *root) {
    // step 1: check for base case if root is null or not

    vector<int> ans;
    if (root == NULL) {
        return ans;
    }

    // step 2: make queue of type Node having node, its hDistance and its level.

    queue<Node> q;
    q.push({root, 0, 0});
    // root is at hDistance 0 and level 0

    map<int, map<int, vector<int>>> nodes;
    // we are using map for sorting of the hDistance and level from smallest to largest
    // for easy copy to final Ans vector.

    // we are using this type of nested map because we have to mark hDistance with
    // its level and any level can have multiple nodes (overalapping nodes) and we have
    // to add these nodes in same order these are existing i.e for if left subtree
    // and right subtree has two overlapping nodes, we will take left first and right
    // after this.

    // thats why, we are doing levelwise traversal because it first inserts left and
    // child of left subtree and then right subtree so overlapping sequence is maintained.
    // But incase we need, smallest first or largest first we can use multiset with
    // greater<int> property :
    // map<int, map<int, multiset<int, greater<int>>>> nodes;

    while (!q.empty()) {
        // step 3: pop out the front node
        Node top = q.front();
        q.pop();

        // extract node, hDistance and level values from popped Node.

        TreeNode<int> *node = top.node;
        int hDistance = top.hDistance;
        int level = top.level;

        // step 4: add the current node's value to corresponding hDistance and level
        // in the nested map data structure.

        nodes[hDistance][level].push_back(node->data);

        // step 5: then insert left and right childs with their updated hDistance and
        // level in the queue

        if (node->left) {
            q.push({node->left, hDistance - 1, level + 1});
        }
        if (node->right) {
            q.push({node->right, hDistance + 1, level + 1});
        }
    }

    // step 6: finally copy the map items to the ans vector

    for (auto it : nodes) { // it variable has pair of int and map<int, vector<int>>
        // p has pair of int and vector<int> (having elements of overlapping nodes)
        for (auto p : it.second) {
            ans.insert(ans.end(), p.second.begin(), p.second.end());
            // insert the elements from begin to end of vector<int> using insert
            // function.
        }
    }

    return ans;
}