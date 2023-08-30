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

// Brute Force Approach using Recursion
// Time Complexity: O(N^2)
// Space Complexity: O(N) {Recursion}

int length(Node *head) { // recursive function for finding length of LL
    if (head == NULL) {
        return 0;
    }

    return 1 + length(head->next);
}

Node* kReverse(Node* head, int k) {
    
    if (head == NULL || head->next == NULL) { // base case
        return head;
    } 
    
    if (k <= 1) { // if there is k = 0 or 1, nothing change
        return head;
    }
    
    int len = length(head); // it calculates the length of the current linkedlist
    if (len < k) { 
        // if it is small than given k, means you dont need to reverse it.
        // means it will not reverse the remaining LL if its length is smaller than k.
        return head;
    }

    else { // if len >= k means you have to reverse
        int count = 0;
    
        Node *curr = head; 
        Node *prev = NULL;
        Node *next = NULL;   
    
        while (count < k && curr != NULL) { // reverse the LL till k
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
            count++;
        }

        if (next != NULL) { 
            // if next is not null, perform recursion and insert it in head->next
            // head will be become last node of reverse LL.
            head->next = kReverse(next, k);
        }

        return prev; // return prev which is final head.
    }
}

// Better Brute Force using Recursion: we can eliminate length function to check for 
// the block is more than the current length of linkedlist

// Time Complexity: O(N)
// Space Complexity: O(N) {Recursion}

Node* kReverse(Node* head, int k) {
    
    if (head == NULL || head->next == NULL) { // base case
        return head;
    } 
    
    if (k <= 1) { // if there is k = 0 or 1, nothing change
        return head;
    }
    
    int count = 0;
    
    Node *curr = head; 
    Node *prev = NULL;
    Node *next = NULL;   
    
    while (count < k && curr != NULL) { // reverse the LL till k
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }

    if (count < k) { 
        // it curr reaches to null means curr size of ll is less than k, dont reverse it.
        curr = prev;
        prev = NULL;
        next = NULL;
        count = 0;

        while (count < k && curr != NULL) { 
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
            count++;
        }
    }

    if (next != NULL) { 
        // if next is not null, perform recursion and insert it in head->next
        // head will be become last node of reverse LL.
        head->next = kReverse(next, k);
    }

    return prev; // return prev which is final head.
}

// Optimal Approach: Iterative Method
// Time Complexity: O(N)
// Space Complexity: O(1)

Node* kReverse(Node* head, int k) {
    if (k <= 1 || head == NULL || head->next == NULL) { // edge cases
        return head;
    }

    Node *curr = head;
    Node *next = NULL;
    Node *prev = NULL;

    Node* newHead = NULL; // pointer for updated linkedlist
    Node *tail = NULL; // pointer for tail of every previous block (reversed block).
    Node *join = NULL; 
    // joining pointer act as head before reversing, after reversal become tail.

    while (curr != NULL) {
        int count = 0; 
        prev = NULL;
        join = curr; // store current to join

        while (count < k && curr != NULL) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
            count++;
        }

        if (count < k) { // if block is bigger than curr linkedlist, again reverse it
            count = 0;
            curr = prev;
            prev = NULL;
            join = curr;

            while (count < k && curr != NULL) {
                next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
                count++;
            }
        }

        if (newHead == NULL) { // if initially newHead is null, mark to curr prev.
            newHead = prev;
        }

        if (tail != NULL) { // there is tail exists, mark the current reversed ll to next of tail.
            tail->next = prev;
        }

        tail = join; // finally update tail.
    }

    return newHead;
}