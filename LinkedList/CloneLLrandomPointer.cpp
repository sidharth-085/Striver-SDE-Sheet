#include <unordered_map>
#include <iostream>
using namespace std;

class Node {
    public:
    int data;
    Node *next;
    Node *random;

    Node (int data) {
        this->data = data;
        next = NULL;
    }
};

// Approach 1: Using Recursion

Node *cloneRandomListHelper(Node *head, unordered_map<Node *, Node *> &visitedHash) {
	if (head == NULL) {
		return NULL;
	}
	/*
	    If we have already processed the current node, 
		then we simply return the cloned version of it.
	*/
	if (visitedHash.find(head) != visitedHash.end()) {
		return visitedHash[head];
	}

	// Create a new node with the label same as old node. (i.e. copy the node).
	Node *node = new Node(head->data);
	/*
	    Save this value in the hash map. This is needed
		since there might be loops during traversal due 
		to randomness of random pointers and this would help us avoid them.
	*/
	visitedHash.insert(make_pair(head, node));
	/* 
	    Recursively copy the remaining linked list
		starting once from the next pointer and then
		from the random pointer. Thus we have two independent
		recursive calls. Finally we update the next and 
		random pointers for the new node created.
	*/
	node->next = cloneRandomListHelper(head->next, visitedHash);
	node->random = cloneRandomListHelper(head->random, visitedHash);

	return node;
}

Node *cloneRandomList(Node *head) {
	// HashMap which holds old nodes as keys and new nodes as its values.
	unordered_map<Node *, Node *> visitedHash;
	return cloneRandomListHelper(head, visitedHash);
} 

// Approach 2: Using Hashmap (Time Complexity: O(N) & Space Complexity: O(N))

Node *cloneRandomList(Node *head) {
    if (head == NULL) {
        return head;
    }
    
    Node *newHead = new Node(head->data);

    Node *temp = head->next;
    Node *newTemp = newHead;

    unordered_map<Node*, Node*> map;
    map[head] = newHead;
    
    while (temp != NULL) {
        Node *newNode = new Node(temp->data);
        newTemp->next = newNode;
        
        map[temp] = newNode;
        
        newTemp = newTemp->next;
        temp = temp->next;
    }

    temp = head;
    newTemp = newHead;

    while (temp != NULL && newTemp != NULL) {
        newTemp->random = map[temp->random];
        temp = temp->next;
        newTemp = newTemp->next;
    }

    return newHead;
}

// Approach 3: Optimal Solution (Time Complexity: O(N^2) & Space Complexity: O(1))

Node* cloneRandomList(Node* head) {
    if (head == nullptr) {
        return nullptr;
    }

    Node* temp = head;

    // Clone the nodes and insert them next to the original nodes
    while (temp != nullptr) {
        Node* next = temp->next;
        temp->next = new Node(temp->data);
        temp->next->next = next;
        temp = next;
    }

    // Assign random pointers for the cloned nodes
    temp = head;
    while (temp != nullptr) {
		temp->next->random = (temp->random == NULL) ? NULL : temp->random->next;
        temp = (temp->next == NULL) ? NULL : temp->next->next;
    }

    // Separate the cloned list from the original list
    Node* newHead = head->next;
	Node* newTemp = newHead;
    temp = head;
    while (temp != nullptr && newTemp != NULL) {
		newTemp->next = (newTemp->next == NULL) ? NULL : newTemp->next->next;
		temp->next = (temp->next == NULL) ? NULL : temp->next->next;

		newTemp = newTemp->next;
		temp = temp->next;
    }

    return newHead;
}