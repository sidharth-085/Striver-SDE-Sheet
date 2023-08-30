#include <iostream>
#include <unordered_map>
#include <stack>
using namespace std;

class BinaryTreeNode {
    public:
    int data;
    BinaryTreeNode *left;
    BinaryTreeNode *right;

    BinaryTreeNode(int data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

// Approach 1: Using Hashmap (same as pair sum in array)
// Time Complexity: O(N)
// Space Complexity: O(N)

bool pairSumHelper(BinaryTreeNode *root, unordered_map<int,int> &map, int k) {
    // step 1: check for base case
    if (root == NULL) {
        return false;
    }

    // step 2: find the complement and check is it currently present in map or not

    int complement = k - root->data;
    if (map[complement] != 0) {
        return true;

    /*
        if we have to print the pairs, update the if condition with below code

        cout << bstVec[start] << " " << bstVec[end] << endl;
    */
    }

    // step 3: if it is not present in map, add the current node's data in map and 
    // search in left and right subtrees

    map[root->data]++;

    bool leftAns = pairSumHelper(root->left, map, k);
    
    bool rightAns = pairSumHelper(root->right, map, k);
    
    // step 4: if any of both left and right subtree get the pair return true.

    return leftAns || rightAns;
}

bool pairSumBst(BinaryTreeNode *root, int k) {
    if (root == NULL) {
        return false;
    }

    unordered_map<int, int> map;
    return pairSumHelper(root, map, k);
}

// Approach 2: Tree to vector using inorder traversal (only for BST)
// for binary tree, we have to sort and apply Two-pointer approach

// Time Complexity: O(N)
// Space Complexity: O(N)

void inorder(BinaryTreeNode *root, vector<int> &ans) {
    if (root == NULL) {
        return;
    }

    inorder(root->left, ans);

    ans.push_back(root->data);

    inorder(root->right, ans);
}

bool pairSumBst(BinaryTreeNode *root, int k) {
    if (root == NULL) {
        return false;
    }

    vector<int> bstVec;
    inorder(root, bstVec);

    int start = 0;
    int end = bstVec.size() - 1;

    while (start < end) {
        if (bstVec[start] + bstVec[end] == k) {
            return true;

        /*
            if we have to print the pairs, update the if condition with below code

            cout << bstVec[start] << " " << bstVec[end] << endl;

            start++;
            end--;

        */
        }
        else if (bstVec[start] + bstVec[end] < k) {
            start++;
        }
        else {
            end--;
        }
    }

    return false;
}

// Approach 3: Using 2 Pointer approach with Stacks (optimal)
// Time Complexity: O(N)
// Space Complexity: O(N)

bool pairSumBst(BinaryTreeNode *root, int k) {
    // step 1: check the edge case

    if (root == NULL) {
        return false;
    }

    // step 2: create two stacks for storing all left most nodes and right most nodes

    stack<BinaryTreeNode*> leftMost; // these stacks act as start and end pointers
    stack<BinaryTreeNode*> rightMost;

    // first push left most nodes in leftMost stack
    BinaryTreeNode *temp = root;
    while (temp != NULL) {
        leftMost.push(temp);
        temp = temp->left;
    }

    // secondly, push right most nodes in rightMost stack
    temp = root;
    while (temp != NULL) {
        rightMost.push(temp);
        temp = temp->right;
    }

    // step 3: run the loop till we reach to the root in both stacks

    while (leftMost.top() != rightMost.top()) {
        BinaryTreeNode *left = leftMost.top();
        BinaryTreeNode *right = rightMost.top();

        // now just compare the values of left + right to k

        if (left->data + right->data == k) {
            return true;

        /* 
            if we have to print all pairs, we will update the code with below code
            for this if condition

            cout << left->data " " << right->data << endl;
        
            BinaryTreeNode *temp = left;
            leftMost.pop();

            if (temp->right != NULL) {
                temp = temp->right;
                while (temp != NULL) {
                    leftMost.push(temp);
                    temp = temp->left;
                }
            } 
        
            temp = right;
            rightMost.pop();

            if (temp->left != NULL) {
                temp = temp->left;
                while (temp != NULL) {
                    rightMost.push(temp);
                    temp = temp->right;
                }
            } 

        */
        }

        // if addition is smaller than required k, then pop the current leftMost node
        // and add the nodes present right of it.

        else if (left->data + right->data < k) {
            BinaryTreeNode *temp = left;
            leftMost.pop();

            if (temp->right != NULL) {
                temp = temp->right;
                while (temp != NULL) {
                    leftMost.push(temp);
                    temp = temp->left;
                }
            } 
        }

        // if addition is bigger than, required k, then pop the current right most node
        // and add the nodes left of it 

        else {
            BinaryTreeNode *temp = right;
            rightMost.pop();

            if (temp->left != NULL) {
                temp = temp->left;
                while (temp != NULL) {
                    rightMost.push(temp);
                    temp = temp->right;
                }
            } 
        }
    }

    return false;
}