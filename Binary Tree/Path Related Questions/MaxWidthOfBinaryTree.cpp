#include <iostream>
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

// Approach 1: Brute Force 
// Time Complexity: O(N*H)
// Space Complexity: O(H)

int getHeight(TreeNode<int> *root) {
    // step 1: check for base case

    if (root == NULL) {
        return 0;
    }

    // step 2: find height of left subtree and right subtree

    int leftHeight = getHeight(root->left);

    int rightHeight = getHeight(root->right);

    return max(leftHeight, rightHeight) + 1; 
    // return which subtree height is maximum + 1.
}

int getLevelWidth(TreeNode<int> *root, int level) {
    // step 1: check for base case, root is null or not && level less than 0 or not.
    if (root == NULL || level < 0) {
        return 0;
    }

    // step 2: check is current level is 0, it is at root return 1 only one node is here

    if (level == 0) {
        return 1;
    }

    // step 3: find left width && right width by decreasing level by 1

    int leftWidth = getLevelWidth(root->left, level - 1);

    int rightWidth = getLevelWidth(root->right, level - 1);

    return leftWidth + rightWidth; // add both width from left and right.
} 

int getMaxWidth(TreeNode<int> *root) {
    // step 1: check for base case

    if (root == NULL) {
        return 0;
    }

    // step 2: now traverse from level to height - 1 and find width at every level
    // and then finally maximize the maxWidth

    int height = getHeight(root);

    int maxWidth = 0;

    for (int level = 0; level < height; level++) {
        int currWidth = getLevelWidth(root, level);

        maxWidth = max(maxWidth, currWidth);
    }
}

// Approach 2: Pre-order traversal
// Time Complexity: O(N)
// Space Complexity: O(N)

void applyPreorder(TreeNode<int> *root, unordered_map<int, int> &nodesAtLevel, int level) {
    if (root == NULL) {
        return;
    }
    
    //  We got a node at current level.
    nodesAtLevel[level]++;
    
    //  Recursive call on left subtree.
    applyPreorder(root->left, nodesAtLevel, level + 1);
    
    //  Recursive call on right subtree.
    applyPreorder(root->right, nodesAtLevel, level + 1);
}

int getMaxWidth(TreeNode<int> *root) {
    /*
        Key will represent the level 
        and value will represent the total 
        number of node corresponds to that level.
    */
    unordered_map<int, int> nodesAtLevel;
    
    /*
        Apply preorder with the array 
        nodesAtLevel and start level with 0.
    */
    applyPreorder(root, nodesAtLevel, 0);
    
    //  Get the maximum width from the filled array.
    int maxWidth = 0;
    for (auto &it : nodesAtLevel) {
        maxWidth = max(maxWidth, it.second);
    }

    return maxWidth;
}

// Approach 3: Using Level Order Traversal

// Time Complexity: O(N)
// Space Complexity: O(N)

int getMaxWidth(TreeNode<int> *root) {
    // step 1: edge case if root is null
    if (root == NULL) {
        return 0;
    }

    // step 2: make maxWidth for storing the answer, and queue for level order
    // traversal

    int maxWidth = 0;

    queue<pair<TreeNode<int>*, int>> q; // queue stores node and its level in it.
    q.push({root, 0}); // add root with its current level 0
    int currWidth = 0;
    int prevLevel = 0;

    // step 3: start level order traversal

    while (!q.empty()) {
        pair<TreeNode<int>*, int> front = q.front(); 
        // take out the current node and level
        q.pop();

        TreeNode<int> *node = front.first;
        int currLevel = front.second;

        // check if the current node level is not equal to prevLevel means we entered to
        // new level and make current width as 1 and prevLevel = currLevel

        if (currLevel != prevLevel) {
            currWidth = 1;
            prevLevel = currLevel;
        }
        else { // if we get the currLevel and prevLevel equal, increase the width
            currWidth++;
        }

        maxWidth = max(maxWidth, currWidth); // finally update the maxWidth

        if (node->left != NULL) { // push left node if exists
            q.push({node->left, currLevel+1});
        } 

        if (node->right != NULL) { // push right node if exists
            q.push({node->right, currLevel+1});
        } 
    }

    return maxWidth; // finally return the answer
}

// Approach 4: Level-order traversal

// Time Complexity: O(N)
// Space Complexity: O(N)

int getMaxWidth(TreeNode<int> *root) {
    if (root == NULL) { // base case
        return 0;
    }

    queue<TreeNode<int>*> q; // queue for storing the nodes at particular level
    q.push(root); // add root for level 0

    int maxWidth = 0;

    while (!q.empty()) {
        int nodesAtLevel = q.size(); // check size of queue for num of nodes at level
 
        maxWidth = max(maxWidth, nodesAtLevel); // update maxWidth with size of queue

        for (int i=0; i<q.size(); i++) { // now pops all nodes at particular level
            TreeNode<int> *node = q.front();
            q.pop();

            // and add left and right nodes for next traversal
            if (node->left != NULL) { 
                q.push(node->left);
            }

            if (node->right != NULL) {
                q.push(node->right);
            }
        }
    }

    return maxWidth; 
}