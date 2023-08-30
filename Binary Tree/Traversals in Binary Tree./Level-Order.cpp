#include <iostream>
#include <vector>
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

// Time Complexity: O(N)
// Space Complexity: O(N)

// Level-Order traversal is similar to BFS algortithm of Graphs

vector<int> getLevelOrder(BinaryTreeNode<int> *root) {
    vector<int> ans;

    if (root == NULL) { // check for root is null or not.
        return ans;
    }

    queue<BinaryTreeNode<int>*> q; // for level-order or BFS, we need a queue
    q.push(root); // add root in queue

    while (!q.empty()) {
        BinaryTreeNode<int> *front = q.front(); // take out the node from queue
        q.pop();

        ans.push_back(front->data); // add its data to ans

        if (front->left != NULL) { // now add left node if not null
            q.push(front->left);
        }

        if (front->right != NULL) { // now add right node if not null
            q.push(front->right);
        }
    }

    return ans;
}