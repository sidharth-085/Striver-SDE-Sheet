#include <iostream>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

// Pre-requesite: Construct Binary tree using inorder and level order traversal

// Approach 1: Using Recursion without Hashset
// Time Complexity: O(N^3)
// Space Complexity: O(N)

// we are using iterators for inorder left and inorder right

int findHeight(vector<int> inorder, int inS, int inE, vector<int> levelorder, int N) {
    if (inS > inE) {
        return -1;
    }

    int rootData = levelorder[0];

    int rootIndex = inS;
    while (inorder[rootIndex] != rootData) {
        rootIndex++;  
    }

    int leftcount = rootIndex - inS;
    int rightcount = inE - rootIndex;

    vector<int> leftLevelOrder;
    vector<int> rightLevelOrder;

    for (int i = 1; i<levelorder.size(); i++) {
        for (int j=inS; j < rootIndex; j++) {
            if (levelorder[i] == inorder[j]) {
                leftLevelOrder.push_back(levelorder[i]);
            }
        }
    }

    for (int i = 1; i<levelorder.size(); i++) {
        for (int j=rootIndex + 1; j <= inE; j++) {
            if (levelorder[i] == inorder[j]) {
                rightLevelOrder.push_back(levelorder[i]);
            }
        }
    }

    int left = findHeight(inorder, inS, rootIndex - 1, leftLevelOrder, leftcount);
    int right = findHeight(inorder, rootIndex + 1, inE, rightLevelOrder, rightcount);

    return max(left, right) + 1;
}

int heightOfTheTree(vector<int> inorder, vector<int> levelorder, int N) {
    return findHeight(inorder, 0, inorder.size() - 1, levelorder, N);
}

// Approach 2: Using Recursion with Hashset
// Time Complexity: O(N^2)
// Space Complexity: O(N)

int findHeight(vector<int> inorder, int inS, int inE, vector<int> levelorder, int N) {
    if (inS > inE) {
        return -1;
    }

    int rootData = levelorder[0];

    int rootIndex = inS;
    while (inorder[rootIndex] != rootData) {
        rootIndex++;  
    }

    int leftcount = rootIndex - inS;
    int rightcount = inE - rootIndex;

    unordered_set<int> leftset;
    
    for (int i = 0; i < rootIndex; i++) {
        leftset.insert(inorder[i]);
    }

    vector<int> leftLevelOrder;
    vector<int> rightLevelOrder;

     for (int i=1; i<levelorder.size(); i++) {
        if (leftset.find(levelorder[i]) != leftset.end()) {
            leftLevelOrder.push_back(levelorder[i]);
        }
        else {
            rightLevelOrder.push_back(levelorder[i]);
        }
    }

    int left = findHeight(inorder, inS, rootIndex - 1, leftLevelOrder, leftcount);
    int right = findHeight(inorder, rootIndex + 1, inE, rightLevelOrder, rightcount);

    return max(left, right) + 1;
}

int heightOfTheTree(vector<int> inorder, vector<int> levelorder, int N) {
    return findHeight(inorder, 0, inorder.size() - 1, levelorder, N);
}

// Approach 3: Another Approach using Queue (little complex)
// Time Complexity: O(N^2)
// Space Complexity: O(N)

class Node { // class to hold, startIndex, endIndex and height of current subtree
    public:
    int height;
    int startIndex;
    int endIndex;
};

int heightOfTheTree(vector<int> inorder, vector<int> levelorder, int N) {
    int height = 0;
    queue<Node> q; // make queue to hold node values

    Node init; // add the initial node
    init.height = 0;
    init.startIndex = 0;
    init.endIndex = N-1;

    // step 1: push the initial node in the queue for starting the traversal

    q.push(init); 

    // step 2: traverse the level order and find the height

    for (int i = 0; i < N; i++) { 
        int rootData = levelorder[i]; 
        // make the level order first element root element
        int rootIndex = -1;

        Node currNode = q.front(); // pop out the node from queue
        q.pop();

        // step 3: find the current root in current inorder from start to end
        
        for (int j = currNode.startIndex; j <= currNode.endIndex; j++) {
            if (rootData == inorder[j]) {
                rootIndex = j;
            }
        }

        // step 4: now check is index at which we found the root is not the 
        // first element of inorder. If not, make the newNode and add the start as 
        // current start and end as one before at which we found the root.

        if (rootIndex > currNode.startIndex) { // for left subtree
            Node newNode;
            newNode.startIndex = currNode.startIndex;
            newNode.endIndex = rootIndex - 1;
            newNode.height = currNode.height + 1; // increase the height by 1

            height = max(height, newNode.height); // is current height is maximum ?

            q.push(newNode); // then push the newNode in queue for traversal
        }

        // step 5: now check is index at which we found the root is not the 
        // last element of inorder. If not, make the newNode and add the start as 
        // one ahead of index at which we found the root and end as end of curr node.

        if (rootIndex < currNode.endIndex) {
            Node newNode;
            newNode.startIndex = rootIndex + 1;
            newNode.endIndex = currNode.endIndex;
            newNode.height = currNode.height + 1; // increase the height by 1 before adding
 
            height = max(height, newNode.height); // maximize the height

            q.push(newNode); // finally push the node in queue for traversal
        } 
    }

    return height;
}

// Approach 4: Using Queue with Map (for inorder)
// Time Complexity: O(N)
// Space Complexity: O(N)

int heightOfTheTree(vector<int> inorder, vector<int> levelorder, int N) {
    int height = 0;
    queue<Node> q; // make queue to hold node values

    Node init; // add the initial node
    init.height = 0;
    init.startIndex = 0;
    init.endIndex = N-1;

    unordered_map<int, int> inMap;
    // use map for adding the element and save time for searching root in inorder 

    for (int i = 0; i < N; i++) {
        inMap[inorder[i]] = i;
    }

    // step 1: push the initial node in the queue for starting the traversal

    q.push(init); 

    // step 2: traverse the level order and find the height

    for (int i = 0; i < N; i++) { 
        int rootData = levelorder[i]; 
        // make the level order first element root element

        int rootIndex = inMap[rootData];
        // find the index where we found the root in inorder

        Node currNode = q.front(); // pop out the node from queue
        q.pop();

        // step 3: now check is index at which we found the root is not the 
        // first element of inorder. If not, make the newNode and add the start as 
        // current start and end as one before at which we found the root.

        if (rootIndex > currNode.startIndex) { // for left subtree
            Node newNode;
            newNode.startIndex = currNode.startIndex;
            newNode.endIndex = rootIndex - 1;
            newNode.height = currNode.height + 1; // increase the height by 1

            height = max(height, newNode.height); // is current height is maximum ?

            q.push(newNode); // then push the newNode in queue for traversal
        }

        // step 4: now check is index at which we found the root is not the 
        // last element of inorder. If not, make the newNode and add the start as 
        // one ahead of index at which we found the root and end as end of curr node.

        if (rootIndex < currNode.endIndex) {
            Node newNode;
            newNode.startIndex = rootIndex + 1;
            newNode.endIndex = currNode.endIndex;
            newNode.height = currNode.height + 1; // increase the height by 1 before adding
 
            height = max(height, newNode.height); // maximize the height

            q.push(newNode); // finally push the node in queue for traversal
        } 
    }

    return height;
}