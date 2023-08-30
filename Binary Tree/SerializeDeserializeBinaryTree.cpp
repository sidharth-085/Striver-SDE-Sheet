#include <iostream>
#include <queue>
#include <string>
#include <sstream>
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

// In this question, we have tree and we have to write two functions i.e. for serialize
// and deserialize. Serialization means convert binary tree in such a way that this
// data of binary tree can be transmitted to networks and then it will be deserialized
// to get the orignal binary tree back.

// Approach using Level order Traversal
// Time Complexity: O(N)
// Space Complexity: O(N)

string serializeTree(TreeNode<int> *root) {
    string serialized;

    // step 1: if given tree is empty, return empty string
    if (root == NULL) {
        return serialized;
    }

    // step 2: for level order traversal, make queue and insert root in it

    queue<TreeNode<int>*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode<int> *node = q.front();
        q.pop();

        // if popped node is null append hash with comma for representing null in 
        // serialized string
        if (node == NULL) {
            serialized.append("#,");
        }
        // if popped node is not null, append its data converting in string with comma
        else {
            serialized.append(to_string(node->data) + ',');
        }
        
        // then finally check is current node is null or not, if not null add its 
        // childrens in queue whether it is null or not

        if (node != NULL) {
            q.push(node->left);
            q.push(node->right);
        }
    }

    return serialized; // finally return string
}

TreeNode<int>* deserializeTree(string &serialized) {
    // step 1: check if given string is empty, return NULL

    if (serialized.size() == 0) {
        return NULL;
    }

    // step 2: make stringstream for separating the string from commas as deliminator

    stringstream ss(serialized);
    string str; // string storing a particular number or hash if null node is there

    getline(ss, str, ','); 
    // this getline function takes stringstream, string and deliminator to store
    // first number as string before comma. As soon as we call getline with given inputs
    // it will iterate to next number before comma and so on

    TreeNode<int> *root = new TreeNode<int>(stoi(str));
    // so now, str stores first number convert it into integer using stoi function and
    // make root

    queue<TreeNode<int>*> q;
    q.push(root);

    // push this root in the queue and start level order traversal for construction 
    // of tree levelwise

    while (!q.empty()) {
        // pop out the node

        TreeNode<int> *node = q.front();
        q.pop();

        // call getline function and shifts to next number and store in string str

        getline(ss, str, ',');

        // if str has hash means it is null child, place null in left
        if (str == "#") { 
            node->left = NULL;
        }

        // if not, make a new node using str and stoi function make the new node as 
        // left child of current popped out node. Also, push it in the queue for 
        // levelwise traversal
        else {
            TreeNode<int> *leftNode = new TreeNode<int>(stoi(str));
            node->left = leftNode;
            q.push(leftNode);
        }

        // repeat same for right subtreee
        getline(ss, str, ',');
        if (str == "#") {
            node->right = NULL;
        }
        else {
            TreeNode<int> *rightNode = new TreeNode<int>(stoi(str));
            node->right = rightNode;
            q.push(rightNode);
        }
    }

    return root; // and finally return root having the orignal tree back. 
}