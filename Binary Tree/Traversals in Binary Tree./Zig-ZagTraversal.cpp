#include <iostream>
#include <queue>
#include <stack>
#include <deque>
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

// Approach 1: Two-stack Approach
// Time Complexity: O(N)
// Space Complexity: O(N)

vector<int> zigZagTraversal(BinaryTreeNode<int> *root) {
    vector<int> answer;

    if (root == NULL) {
        return answer;
    }
    // Declare two empty stacks for odd level and even level
    stack<BinaryTreeNode<int>*> oddLevel, evenLevel;

    // Push root to odd level
    oddLevel.push(root);

    // Run a loop until both stacks are not empty
    while (evenLevel.empty() == false or oddLevel.empty() == false) {

        // Pop nodes from odd level and push it into even level
        while (oddLevel.empty() == false) {

            // Pop the top node odd level
            BinaryTreeNode<int>* topNode = oddLevel.top();
            oddLevel.pop();

            // Add data of popped node to the answer
            answer.push_back(topNode->data);

            // Push left and right child of popped node to
            // Even level stack
            if (topNode->left) {
                evenLevel.push(topNode->left);
            }
            if (topNode->right) {
                evenLevel.push(topNode->right);
            }
        }

        // Pop nodes from even level and push it into odd level
        while (evenLevel.empty() == false) {
            BinaryTreeNode<int>* topNode = evenLevel.top();
            evenLevel.pop();

            // Add data of popped node to the answer
            answer.push_back(topNode->data);

            // Push right and left child of popped node to
            // odd level stack
            if (topNode->right) {
                oddLevel.push(topNode->right);
            }
            if (topNode->left) {
                oddLevel.push(topNode->left);
            }
        }
    }

    // Return the answer
    return answer;
}

// Approach 2: Using Deque data structure, its allows pushing elements and popping 
// elements from both directions

// Time Complexity: O(N)
// Space Complexity: O(N)

vector<int> zigZagTraversal(BinaryTreeNode<int> *root) {
    // step 1: base case
    vector<int> ans;

    if (root == NULL) {
        return ans;
    }
    
    // step 2: make deque (double - ended queue) for level order traversal

    deque<BinaryTreeNode<int>*> dq;
    dq.push_back(root);
    bool leftToRight = true; // flag for left to right or right to left traversal

    while (!dq.empty()) {
        int nodesAtLevel = dq.size(); // find number of nodes at each level

        for (int i=0; i<nodesAtLevel; i++) {
            if (leftToRight == true) { // flag is positive, traverse left to right
                BinaryTreeNode<int> *node = dq.front();
                dq.pop_front();

                ans.push_back(node->data); // push elements and pop elements from front

                if (node->left) { // insert left first
                    dq.push_back(node->left);
                }

                if (node->right) { // and then right
                    dq.push_back(node->right);
                }
            }
            else { // if flag is flase, traverse right to left
                BinaryTreeNode<int> *node = dq.back(); 
                dq.pop_back();

                ans.push_back(node->data); // add elements from back to front

                if (node->right) { // insert elements in deque, right first in front
                    dq.push_front(node->right);
                }

                if (node->left) { // then insert left to front
                    dq.push_front(node->left);
                }
            }
        }

        leftToRight = !leftToRight; // change the flag
    }

    return ans;
}

// Approach 3: Optimal Approach using Queue

// Time Complexity: O(N)
// Space Complexity: O(N)

vector<int> zigZagTraversal(BinaryTreeNode<int> *root) {
    // step 1: check for base case

    vector<int> ans;
    if (root == NULL) {
        return ans;
    }

    // step 2: make queue for level order traversal

    queue<BinaryTreeNode<int>*> q;
    q.push(root);
    int level = 0;

    while (!q.empty()) {
        int nodesAtLevel = q.size(); // find the number of nodes at level

        vector<int> data; // make additional vector to store nodes at each level
        for (int i = 0; i < nodesAtLevel; i++) {
            BinaryTreeNode<int> *node = q.front();
            q.pop();

            data.push_back(node->data); // add the nodes of each level to data.

            if (node->left) {
                q.push(node->left);
            }
            if (node->right) {
                q.push(node->right);
            }
        }

        // step 3: now check if level is even, push in left to right direction in ans
        // else, push in right to left direction in ans

        int size = data.size();
        for (int i=0; i<size; i++) {
            if (level % 2 == 0) {
                ans.push_back(data[i]);
            }
            else {
                ans.push_back(data[size-i-1]);
            }
        }

        level++; // increase level to keep track of each level
    }

    return ans;
}