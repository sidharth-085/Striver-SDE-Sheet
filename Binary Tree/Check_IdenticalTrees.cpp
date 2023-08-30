#include <iostream>
#include <queue>
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

// Approach 1: Recursive Approach (DFS)

// Time Complexity: O(N)
// Space Complexity: O(N)

bool identicalTrees(BinaryTreeNode<int>* root1, BinaryTreeNode<int>* root2) {
    if (root1 == NULL && root2 == NULL) { // if both roots are null, trees are identical
        return true;
    }

    if (root1 == NULL || root2 == NULL) {
        return false;  // One of the nodes is NULL while the other is not
    }

    if (root1->data != root2->data) { // if root's data is not matching, return false
        return false;
    }
    
    bool leftAns = identicalTrees(root1->left, root2->left); // traverse left subtree

    bool rightAns = identicalTrees(root1->right, root2->right); // traverse right subtree

    return leftAns && rightAns; // if both subtrees are identical, means both trees are identical
}

// Approach 2: Level-order Traversal (BFS)

// Time Complexity: O(N)
// Space Complexity: O(N)

bool identicalTrees(BinaryTreeNode<int>* root1, BinaryTreeNode<int>* root2) {
    // queues for level order traversals

    queue<BinaryTreeNode<int>*> q1;
    queue<BinaryTreeNode<int>*> q2;

    q1.push(root1);
    q2.push(root2);

    while (!q1.empty() && !q2.empty()) {
        BinaryTreeNode<int> *node1 = q1.front();
        q1.pop();

        BinaryTreeNode<int> *node2 = q2.front();
        q2.pop();

        if (node1 == NULL && node2 == NULL) {
            continue;  // Both nodes are NULL, move to the next iteration
        }

        if (node1 == NULL || node2 == NULL) {
            return false;  // One of the nodes is NULL while the other is not
        }

        if (node1->data != node2->data) {
            return false;  // Values of nodes are different
        }

        q1.push(node1->left);
        q1.push(node1->right);

        q2.push(node2->left);
        q2.push(node2->right);
    }

    // Ensure that both queues are empty, indicating both trees have the same number 
    // of nodes

    return q1.empty() && q2.empty();
}