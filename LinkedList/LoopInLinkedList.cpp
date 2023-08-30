#include <iostream>
#include <unordered_map>
using namespace std;

class Node {
    public:
    int data;
    Node *next;

    Node (int data) {
        this->data = data;
        next = NULL;
    }

};

// Approach 1: Using Nested-Loops (Brute Force)

Node *firstNode(Node *head) {
    if (head == NULL || head->next == NULL) {
        return NULL;
    }

    int countForOuterLoop = 0;
    Node *outerLoopNode = head;

    while (outerLoopNode != NULL) {
        countForOuterLoop++;
        outerLoopNode = outerLoopNode->next;

        int countForInnerLoop = countForOuterLoop;
        Node *innerLoopNode = head;
        while (countForInnerLoop > 0) {
            if (innerLoopNode == outerLoopNode) {
                return innerLoopNode;
            }
            innerLoopNode = innerLoopNode->next;
            countForInnerLoop--;
        }
    }
}

// Approach 2: Using Hashtable, Hashset or vector

Node *firstNode(Node *head) {
    if (head == NULL || head->next == NULL) {
        return NULL;
    }

    unordered_map<Node*, bool> visited;
    Node *temp = head;
    while (temp != NULL) {
        if (visited[temp] == true) { // when the node found again and visited return that node.
            return temp;
        }
        visited[temp] = true; // mark the node visited.
        temp = temp->next;
    }
    return NULL;
}

// Approach 3: Floyd - cycle detection Algorithm

Node *firstNode(Node *head) {
    if (head == NULL || head->next == NULL) {
        return NULL;
    }

    Node *slow = head;
    Node *fast = head;

    bool isCycleDetected = false;

    while (slow != NULL && fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            isCycleDetected = true; // when the both pointers colloid cycle is found.
            break;
        }
    }

    if (!isCycleDetected) { // check is cycle is not found then, return null.
        return NULL;
    }

    slow = head; // after the cycle found, reset the slow to head.
    while (slow != fast) {
        // keep slow and fast moving with same speed and when both meets, that location 
        // node we have to return.
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

// this only returns is cycle present or not.

bool detectCycle(Node *head) {
    if (head == NULL || head->next == NULL) {
        return false;
    }

	Node *slow = head;
    Node *fast = head;

    while (slow != NULL && fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}