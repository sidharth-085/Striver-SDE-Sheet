#include <unordered_map>
#include <iostream>
using namespace std;

class Node {
    public:
    int *data;
    Node *next;

    Node (int data) {
        this->data = new int;
        *(this->data) = data;
        next = NULL;
    }
};

// Approach 1: Using Brute Force Method

Node* findIntersection(Node *firstHead, Node *secondHead) {
    Node *firstHeadTemp = firstHead;

    // For every node of first list, traverse the second list and check if there is intersection.
    while (firstHeadTemp != NULL) {
        Node *secondHeadTemp = secondHead;
        while (secondHeadTemp) {
            if (firstHeadTemp == secondHeadTemp) {
                return firstHeadTemp;
            }
            secondHeadTemp = secondHeadTemp->next;
        }
        firstHeadTemp = firstHeadTemp->next;
    }

    // If there is no intersection, return NULL.
    return NULL;
}

// Approach 2: Using Hashing

Node* findIntersection(Node *firstHead, Node *secondHead) { 
    unordered_map<Node*, bool> map;

    Node *temp = firstHead;
    while (temp != NULL) {
        map[temp] = true;
        temp = temp->next;
    }

    temp = secondHead;
    while (temp != NULL) {
        if (map[temp] == true) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Approach 3: Optimized solution

int length(Node *head) {
    Node *temp = head;
    int count = 0;
    while (temp != NULL) {
        temp = temp->next;
        count++;
    }
    return count;
}

Node* findIntersection(Node *firstHead, Node *secondHead) {
    // Step 1: Count lengths of both linkedlists
    int len1 = length(firstHead);
    int len2 = length(secondHead);

    if (len1 > len2) { 
        // check which linkedlist is bigger and brings the pointer to diff of both LL forward.
        int diff = len1-len2;
        while (diff--) {
            firstHead = firstHead->next;
        }
    }
    else {
        // check which linkedlist is bigger and brings the pointer to diff of both LL forward.
        int diff = len2-len1;
        while (diff--) {
            secondHead = secondHead->next;
        }
    }

    // Step 3: After taking bigger linkedlist's head forward, start moving pointers of both LL
    // and check for intersection of both pointers, if get return that node else return null.
    while (firstHead != NULL && secondHead != NULL) {
        if (firstHead == secondHead) {
            return firstHead;
        }
        firstHead = firstHead->next;
        secondHead = secondHead->next;
    }
    return NULL;
}