#include <iostream>
#include <unordered_map>
using namespace std;

// Approach 1: Using an array of the pair class.

class LRUCache {
    pair<int, int> *arr;    // Array to store key-value pairs
    int capacity;           // Maximum capacity of the cache
    int nextIndex;          // Next available index in the array

public:
    LRUCache(int capacity) {
        arr = new pair<int, int>[capacity];
        this->capacity = capacity;
        nextIndex = 0;
    }

private:
    // Helper function to find the index of a given key in the array
    int getKeyIndex(int key) {
        for (int i = 0; i < nextIndex; i++) {
            if (arr[i].first == key) {
                return i;
            }
        }
        return -1;  // Key not found
    }

    // Helper function to shift the elements to the left starting from the given index
    void leftShift(int start) {
        if (start == nextIndex) {
            return;
        }

        for (int i = start; i < nextIndex; i++) {
            arr[i - 1] = arr[i];
        }
    }

public:
    // Function to get the value corresponding to a key in the cache
    int get(int key) {
        int keyIndex = getKeyIndex(key);
        if (keyIndex == -1) {
            return -1;  // Key not found
        }

        int value = arr[keyIndex].second;

        leftShift(keyIndex + 1);
        arr[nextIndex - 1] = {key, value};

        return value;
    }

    // Function to insert or update a key-value pair in the cache
    void put(int key, int value) {
        int keyIndex = getKeyIndex(key);

        if (keyIndex == -1) {
            if (nextIndex < capacity) {
                arr[nextIndex] = {key, value};
                nextIndex++;
            } else {
                leftShift(1);
                arr[nextIndex - 1] = {key, value};
            }
        } else {
            leftShift(keyIndex + 1);
            arr[nextIndex - 1] = {key, value};
        }
    }
};

// Approach using Doubly Linked List & Map
// Time Complexity: O(Q).
// where Q is the number of queries given

class Node {
public:
    int key, value;
    Node *left;
    Node *right;

    Node(int key, int value) {
        this->key = key;
        this->value = value;
        left = NULL;
        right = NULL;
    }
};

class LRUCache {
    Node *head;
    Node *tail;
    unordered_map<int, Node*> map; // Map to store key-node pairs
    int capacity;
    int nextIndex;

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        nextIndex = 0;
        head = NULL;
        tail = NULL;
    }

private:
    // Helper function to add a node to the rear of the doubly linked list
    void addToRear(Node *node) {
        if (head == NULL) {
            head = node;
            tail = node;
            return;
        }

        tail->right = node;

        node->left = tail;
        node->right = NULL;
        tail = node;
    }

    // Helper function to delete a node from the doubly linked list
    void deleteNode(Node *node) {
        if (node->left != NULL) {
            node->left->right = node->right;
        } else {
            head = node->right;
        }

        if (node->right != NULL) {
            node->right->left = node->left;
        } else {
            tail = node->left;
        }

        node->left = NULL;
        node->right = NULL;
    }

public:
    // Function to get the value corresponding to a key in the cache
    int get(int key) {
        if (map.find(key) == map.end()) {
            return -1;  // Key not found
        }
        Node *keyNode = map[key];
        deleteNode(keyNode);
        addToRear(keyNode);

        return keyNode->value;
    }

    // Function to insert or update a key-value pair in the cache
    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            Node *keyNode = map[key];
            deleteNode(keyNode);
            addToRear(keyNode);
            keyNode->value = value;
        } 
        else {
            Node *keyNode = new Node(key, value);
            map[key] = keyNode;

            if (nextIndex == capacity) {
                map.erase(head->key);
                deleteNode(head);
                addToRear(keyNode);
            } 
            else {
                addToRear(keyNode);
                nextIndex++;
            }
        }
    }
};