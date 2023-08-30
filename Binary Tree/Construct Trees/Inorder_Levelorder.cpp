#include <iostream>
#include <unordered_set>
using namespace std;

class TreeNode {
    public:
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

// Approach 1: Brute Force method with Recursion
// Time Complexity: O(N^3)
// Space Complexity: O(N)

// here we cant use itertors for level order, because for left or right subtree are 
// not contigious. But we can use for inorder, inS and inE and avoid extra inorder 
// arrays for left and right

TreeNode* getTreeFromInorderAndLevelorder(int n, vector<int> &inorder, vector<int> &levelorder) {
	// step 1: check the base case, either size of inorder or levelorder is zero
	if (inorder.size() == 0 || levelorder.size() == 0) {
		return NULL;
	}

    // step 2: level order's first element is root, make the node for root

	int rootData = levelorder[0];
	TreeNode *root = new TreeNode(rootData);

    // step 3: find the rootIndex in inorder using rootData

	int rootIndex = 0;
	while (inorder[rootIndex] != rootData) {
		rootIndex++;
	}

	// step 4: make the left and right inorder arrays

	vector<int> leftInorder;
	
    // from starting to just before rootIndex => left inorder
	for (int i=0; i<rootIndex; i++) { 
		leftInorder.push_back(inorder[i]);
	}

	vector<int> rightInorder;

    // from rootIndex + 1 to end of inorder => right inorder
	for (int i=rootIndex+1; i<inorder.size(); i++) {
		rightInorder.push_back(inorder[i]);
	}

	// step 5: make left and right level order arrays

	vector<int> leftLevelOrder;

	for (int i=1; i<levelorder.size(); i++) {
		int value = levelorder[i];

		for (int j=0; j<leftInorder.size(); j++) {
			if (value == leftInorder[j]) {
				leftLevelOrder.push_back(value);
			}
		}
	}

	vector<int> rightLevelOrder;

	for (int i=1; i<levelorder.size(); i++) {
		int value = levelorder[i];

		for (int j=0; j<rightInorder.size(); j++) {
			if (value == rightInorder[j]) {
				rightLevelOrder.push_back(value);
			}
		}
	}

    // step 6: finally call for recursion, on both left and right subtree with their
    // respective inorder and levelorder vectors

	root->left = getTreeFromInorderAndLevelorder(leftInorder.size(), leftInorder, leftLevelOrder);
	root->right = getTreeFromInorderAndLevelorder(rightInorder.size(), rightInorder, rightLevelOrder);

	// instead of making left and right inorder separate arrays, we can use iterators
	// starting inS to rootIndex - 1 for left inorder && rootIndex + 1 to inE for right
	// inorder
	
	return root;
}

// Approach 2: Using Hashset and Recursion
// Time Complexity: O(N^2)
// Space Complexity: O(N)

// here we cant use itertors for level order, because for left or right subtree are 
// not contigious. But we can use for inorder, inS and inE and avoid extra inorder 
// arrays for left and right

TreeNode* getTreeFromInorderAndLevelorder(int n, vector<int> &inorder, vector<int> &levelorder) {
    // step 1: check the base case, either size of inorder or levelorder is zero
	if (inorder.size() == 0 || levelorder.size() == 0) {
		return NULL;
	}

    // step 2: level order's first element is root, make the node for root

	int rootData = levelorder[0];
	TreeNode *root = new TreeNode(rootData);

    // step 3: find the rootIndex in inorder using rootData

	int rootIndex = 0;
	while (inorder[rootIndex] != rootData) {
		rootIndex++;
	}

/* IMPORTANT
    we can use below code instead of using more loops and set for right subtree

    unordered_set<int> leftSet;
	vector<int> leftInorder;
	vector<int> rightInorder;

	for (int i=0; i<inorder.size(); i++) { 
		if (i < rootIndex) { // before rootIndex => left subtree
			leftSet.insert(inorder[i]);
			leftInorder.push_back(inorder[i]);
		}

        // traverse the complete inorder skiping root,

		else if (i > rootIndex) { // after rootIndex =>right subtree
			rightInorder.push_back(inorder[i]);
		}
	}

	vector<int> leftLevelOrder;
	vector<int> rightLevelOrder;

	for (int i=1; i<levelorder.size(); i++) {
        // if levelorder[i] present in leftSet, add it to leftLevelOrder 
        // else add it to rightLevelOrder

		if (leftSet.find(levelorder[i]) != leftSet.end()) {
			leftLevelOrder.push_back(levelorder[i]);
		}
		else {
			rightLevelOrder.push_back(levelorder[i]);
		}
	}
*/

    // step 4: after finding partitioning point of left and right subtrees, make left
    // inorder and level order && right inorder and level order using hashsets

	unordered_set<int> leftSet;
    // we use keftSet for checking is current element is part of left Subtree or not

	vector<int> leftInorder;

    // from starting to just before rootIndex => left inorder
	for (int i=0; i<rootIndex; i++) { 
		leftSet.insert(inorder[i]);
		leftInorder.push_back(inorder[i]);
	}

	vector<int> leftLevelOrder;
	for (int i=1; i<levelorder.size(); i++) {
		if (leftSet.find(levelorder[i]) != leftSet.end()) {
			leftLevelOrder.push_back(levelorder[i]);
		}
	}

	unordered_set<int> rightSet; 
    // we use rightSet for checking is current element is part of right Subtree or not

	vector<int> rightInorder;

    // from rootIndex + 1 to end of inorder => right inorder
	for (int i=rootIndex+1; i<inorder.size(); i++) {
		rightSet.insert(inorder[i]);
		rightInorder.push_back(inorder[i]);
	}

	vector<int> rightLevelOrder;
	for (int i=1; i<levelorder.size(); i++) {
		if (rightSet.find(levelorder[i]) != rightSet.end()) {
			rightLevelOrder.push_back(levelorder[i]);
		}
	}

    // step 5: finally call for recursion, on both left and right subtree with their
    // respective inorder and levelorder vectors

	root->left = getTreeFromInorderAndLevelorder(n, leftInorder, leftLevelOrder);
	root->right = getTreeFromInorderAndLevelorder(n, rightInorder, rightLevelOrder);

	// instead of making left and right inorder separate arrays, we can use iterators
	// starting inS to rootIndex - 1 for left inorder && rootIndex + 1 to inE for right
	// inorder

	return root;
}