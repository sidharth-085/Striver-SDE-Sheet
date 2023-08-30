#include <iostream>
#include <stack>
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

// In this question, we divide the problem in 3 parts (left boundry, leaf nodes & right
// nodes) and do it separately. We can use extra space left and right but no need.

// Approach 1: Recursive Approach 
// Time Complexity: O(N)
// Space Complexity: O(N) 
// {here we are not using any extra space but recursion takes space}

void leafNodes(TreeNode<int> *root, vector<int> &ans) { // recursive leaf nodes
    if (root == NULL) {
        return;
    }

    if (root->left == NULL && root->right == NULL) {
        ans.push_back(root->data);
    }

    leafNodes(root->left, ans);
    leafNodes(root->right, ans);
}

void leftBoundary(TreeNode<int> *root, vector<int> &leftAns) { // recursive left boundary
    if (root->left == NULL && root->right == NULL) {
        return;
    }

    leftAns.push_back(root->data);

    if (root->left) {
        leftBoundary(root->left, leftAns);
    }
    else {
        leftBoundary(root->right, leftAns);
    }
}

void rightBoundary(TreeNode<int> *root, vector<int> &rightAns) { // recursive right boundary
    if (root->left == NULL && root->right == NULL) {
        return;
    }

    if (root->left) {
        rightBoundary(root->left, rightAns);
    }
    else {
        rightBoundary(root->right, rightAns);
    }

    rightAns.push_back(root->data);
}

vector<int> traverseBoundary(TreeNode<int> *root) {
    // step 1: base case

    vector<int> finalAns;
    if (root == NULL) {
        return finalAns;
    }

    // step 2: now first add the root data in finalAns.

    finalAns.push_back(root->data);

    // step 3: find the left boundary traversal from leftBoundary function using 
    // preorder function

    leftBoundary(root->left, finalAns);

    // step 4: find all the leaf nodes from leafNodes function using preorder function

    leafNodes(root, finalAns);

    // step 5: find the right boundary traversal in bottom to top so we use post order
    // traversal

    rightBoundary(root->right, finalAns);

    // step 6: finally got all the answers stored in vector and we can return it.

    return finalAns;
}

// Approach 2: Iterative Approach (for left and right boundary)
// Time Complexity: O(N)
// Space Complexity: O(N)
// here we are using stack for right boundary traversal so extra space is needed

void leafNodes(TreeNode<int> *root, vector<int> &ans) {
    if (root == NULL) {
        return;
    }

    if (root->left == NULL && root->right == NULL) {
        ans.push_back(root->data);
    }

    leafNodes(root->left, ans);
    leafNodes(root->right, ans);
}

void leftBoundary(TreeNode<int> *root, vector<int> &leftAns) {
    TreeNode<int> *temp = root;

    while (temp != NULL) {
        if (temp->left == NULL && temp->right == NULL) {
            break;
        }

        if (temp->left != NULL) {
            leftAns.push_back(temp->data);
            temp = temp->left;
        }
        else {
            leftAns.push_back(temp->data);
            temp = temp->right;
        }
    }
}

void rightBoundary(TreeNode<int> *root, stack<int> &stk) {
    TreeNode<int> *temp = root;

    while (temp != NULL) {
        if (temp->left == NULL && temp->right == NULL) {
            break;
        }
        if (temp->right != NULL) {
            stk.push(temp->data);
            temp = temp->right;
        }
        else {
            stk.push(temp->data);
            temp = temp->left;
        }
    }
}

vector<int> traverseBoundary(TreeNode<int> *root) {
    // step 1: base case

    vector<int> finalAns;
    if (root == NULL) {
        return finalAns;
    }

    // step 2: now first add the root data in finalAns.

    finalAns.push_back(root->data);

    // step 3: find the left boundary traversal from leftBoundary function.

    vector<int> leftAns;
    leftBoundary(root->left, leftAns);

    // step 4: find all the leaf nodes from leafNodes function.

    vector<int> leafs;
    leafNodes(root, leafs);

    // step 5: find the right boundary traversal in bottom to top so we use stack in 
    // this case

    stack<int> stk;
    rightBoundary(root->right, stk);

    // step 6: after getting all answers for left, leaf and right boundary, merge
    // all of them in finalAns vector and return.

    for (int i=0; i<leftAns.size(); i++) {
        finalAns.push_back(leftAns[i]);
    }

    for (int i=0; i<leafs.size(); i++) {
        finalAns.push_back(leafs[i]);
    }

    while (!stk.empty()) {
        int top = stk.top();
        stk.pop();

        finalAns.push_back(top);
    }

    return finalAns;
}