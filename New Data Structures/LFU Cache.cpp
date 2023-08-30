#include <iostream>
#include <unordered_map>
using namespace std;

// Approach: Using Doubly Linkedlist && hashmaps
// Time Complexity: O(Q)
// Q is number of queries

// Space Complexity: O(N)
// N is capacity given

class Node { // node for doubly linkedlist
    public:
    int key, value, freq;
    Node *prev;
    Node *next;

    Node(int key, int value) {
        this->key = key;
        this->value = value;
        freq = 1;
        prev = NULL;
        next = NULL;
    }
};

class List { // doubly linkedlist for storing different nodes with same frequency
    public:

    int size; // size of the linkedlist
    Node *head;
    Node *tail;

    List() {
        head = NULL;
        tail = NULL;
    }

    void addToRear(Node *node) { // it will add the node to the last
        if (head == NULL) {
            head = node;
            tail = node;
            return;
        }

        tail->next = node;
        node->prev = tail;

        node->next = NULL;
        tail = node;
        size++;
    }

    void removeNode(Node *node) { // it will remove the node
        if (node->next != NULL) {
            node->next->prev = node->prev;
        }
        else {
            tail = node->prev;
        }

        if (node->prev != NULL) {
            node->prev->next = node->next;
        }
        else {
            head = node->next;
        }

        node->next = NULL;
        node->prev = NULL;
        size--;
    }
};

class LFUCache {
    unordered_map<int, Node*> keyNodeMap; // map to store key and its node pair
    unordered_map<int, List*> freqListMap; // map to store freq and linkedlist pair
    int capacity;
    int nextIndex;
    int minFreq; // min freq in the LFU cache to be used

    void updateFreqListMap(Node *node) { // Imp function
        // step 1: first erase the node from both maps

        keyNodeMap.erase(node->key);
        freqListMap[node->freq]->removeNode(node);

        // step 2: check if after removing of node from both maps, the node's freq
        // linkedlist size is 0 && current node freq is min freq, increment to next.

        if (node->freq == minFreq && freqListMap[node->freq]->size == 0) {
            minFreq++;
        }

        // step 3: make a new doubly linkedlist for next freq if it is not present 
        // already in map.

        List *nextHigherFreqList = new List();
        if (freqListMap.find(node->freq + 1) != freqListMap.end()) {
            nextHigherFreqList = freqListMap[node->freq + 1];
        }

        node->freq++; // increase the frequency by 1
        nextHigherFreqList->addToRear(node); // add the current node to the rear of new list

        // step 4: finally add back to both maps with changed list.

        keyNodeMap[node->key] = node; 
        freqListMap[node->freq] = nextHigherFreqList;
    }

    public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        nextIndex = 0;
        minFreq = 0;
    }

    int get(int key) { 
        // step 1: first check is key exists in LFU cache or not

        if (keyNodeMap.find(key) != keyNodeMap.end()) {
            Node *node = keyNodeMap[key]; // keep the node
            updateFreqListMap(node); // update its frequency and freqListMap
            return node->value;
        } 
        return -1; // if not found in LFU, return -1.
    }

    void put(int key, int value) {
        if (capacity == 0) { // if given capacity is 0, return.
            return;
        }

        // check if there is key exists already

        if (keyNodeMap.find(key) != keyNodeMap.end()) {
            Node *node = keyNodeMap[key];
            node->value = value;
            updateFreqListMap(node); // put new value and update the freqlistmap & freq.
            return;
        } 

        if (nextIndex == capacity) { 
            // if it is not present, we have to create new node and list
            List *list = freqListMap[minFreq]; 
            
            // but first have to delete the minFreq node from both maps.
            keyNodeMap.erase(list->head->key); // erase the head from list

            list->removeNode(list->head); 
            // erase the head node, because we are keeping recently used node at ending 
            // (LRU).
            
            nextIndex--; // decrease the nextIndex
        }

        nextIndex++; // now for adding we have to increase nextIndex
        minFreq = 1; // for new key and value minFreq should be 1

        List *newList = new List();
        if (freqListMap.find(minFreq) != freqListMap.end()) { 
            // check if already minFreq = 1 exists in map
            newList = freqListMap[minFreq];
        }

        // if not make new list for min freq.

        Node* node = new Node(key, value); // make a new node for given key and value.
        newList->addToRear(node); // add to the rear, to mark it recently used
       
        keyNodeMap[key] = node; 
        freqListMap[minFreq] = newList; // add the node & list back to maps.
    }
};