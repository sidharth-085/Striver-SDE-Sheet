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

// Approach 1: Reverse the linkedlist and delete kth node from front

// Time Complexity: O(N)
// Space Complexity: 

Node *reverseLL(Node *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    Node *newHead = reverseLL(head->next);
    head->next->next = head;
    head->next = NULL;
    return newHead;
}

Node* removeKthNode(Node* head, int K) {
    if (head == NULL || head->next == NULL) { 
        // check if head is null or have single node
        return NULL;
    }
    
    // step 1: reverse the linkedlist to start from front
    Node *newHead = reverseLL(head);

    int count = 1; // start counting from 1
    Node *temp = newHead;
    Node *prev = NULL;

    while (count < K) { // update count, prev and temp
        count++;
        prev = temp;
        temp = temp->next;
    }

    // delete node
    if (temp == newHead && prev == NULL) { // if k = 1, then prev = NULL & temp = newHead
        prev = newHead; 
        newHead = newHead->next; // move newHead forward and delete prev
        delete prev;
    }
    else {
        prev->next = temp->next; // if not, now delete the node
        temp->next = NULL;
        delete temp;
    }

    head = reverseLL(newHead); // finally reverse the linkedist and return.

    return head;
}

// Approach 2: Reach to the kth node from last and delete accordingly

// Time Complexity: O(N)
// Space Complexity: O(1)

int length(Node *head) {
    int count = 0;

    Node *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}

Node* removeKthNode(Node* head, int K) {
    if (head == NULL || head->next == NULL) {
        return NULL;
    }
    Node *temp = head;
    Node *prev = NULL;

    int len = length(head);
    int pos = len-K+1;

    int count = 1;

    while (count < pos && temp != NULL) { // reach to the position
        count++;
        prev = temp;
        temp = temp->next;
    }

    if (prev == NULL && temp == head) { // check if the prev is still null
        prev = head;
        head = head->next;
        delete prev;
    } 
    else {
        prev->next = temp->next;
        if (temp->next != NULL) {
            temp->next = NULL;
        }
        delete temp;
    }

    return head;
}

// Approach 3: Slow and Fast Pointer approach

// Time Complexity: O(N)
// Space Complexity: O(1)

Node *removeKthNode(Node *head, int K) {
    if (head == NULL || K == 0) {
        return head;
    }

    Node *slow = head;
    Node *fast = head;

    for (int i = 0; i < K; i++) {
        // If head is the Kth node from end of Linked List.
        if (fast->next == NULL) {
            Node *next = head->next;
            head->next = NULL;
            head = next;

            return head;
        }

        else {
            fast = fast->next;
        }
    }

    // Moving both slow and fast pointer with same speed.
    while (fast->next != NULL) {
        slow = slow->next;
        fast = fast->next;
    }

    // Removing the Kth node from end of Linked List.
    slow->next = slow->next->next;

    return head;
}