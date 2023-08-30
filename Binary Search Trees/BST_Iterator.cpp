#include <iostream>
#include <vector>
#include <stack>
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

// BST iterator is the class which gives the inorder fashion elements using the next
// function and check is next element is present in BST or not using hasNext function.

// Approach 1: Using In-order Traversal (flattening the BST)
// Time Complexity: O(N)
// Space Complexity: O(N)

class BSTiterator {
    vector<int> inorder;
    int nextIndex;

    // converts the binary search tree into sorted array using inorder traversal
    void inorderTraversal(TreeNode<int> *root, vector<int> &ans) {
        if (root == NULL) {
            return;
        }

        inorderTraversal(root->left, ans);

        ans.push_back(root->data);

        inorderTraversal(root->right, ans);
    }   

    public: 
    BSTiterator(TreeNode<int> *root) {
        nextIndex = 0; // keeping track of every element
        inorderTraversal(root, inorder);
        // call inorder on root to fill inorder array
    }

    int next() {
        int nextSmallest = inorder[nextIndex];
        nextIndex++;
        // save the nextSmallest element and increment the nextIndex

        return nextSmallest;
    }

    bool hasNext() {
        if (nextIndex == inorder.size()) { 
            // if nextIndex reached to size of inorder, means tree is empty and it
            // does not have any next smallest element
            return false;
        }
        // if it has some elements return true.
        return true;
    }
};

// Approach 2: Using Stack in different way
// Time Complexity: O(N)
// Space Complexity: O(N)

class BSTiterator {
    public: 
    stack<TreeNode<int>*> stk;
    // stack first stores the all left most nodes and then add elements according to
    // next() function call

    // function to add left most nodes of given root of tree
    void leftMostNodes(TreeNode<int> *root) {
        if (root == NULL) {
            return;
        }

        TreeNode<int> *temp = root;
        while (temp != NULL) {
            stk.push(temp);
            temp = temp->left;
        }
    }

    // on calling constructor, add all left nodes of given BST to stack
    BSTiterator(TreeNode<int> *root) {
        leftMostNodes(root);
    }

    int next() {   
        TreeNode<int> *nextSmallest = stk.top();
        stk.pop();
        // pop out the top node of stack which is current smallest
        
        // now check, is current popped node has its right child, if it have add
        // all leftmost nodes of node->right to stack

        if (nextSmallest->right != NULL) {
            leftMostNodes(nextSmallest->right);
        }

        return nextSmallest->data;
        // finally return nextSmallest's data 
    }

    bool hasNext() {
        if (stk.size() == 0) { // if stack is empty means tree is empty now.
            return false;
        }
        return true;
    }
};