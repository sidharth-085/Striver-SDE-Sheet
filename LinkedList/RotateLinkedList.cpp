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

// Approach using Circular Linkedlist
// Time Complexity: O(N)
// Space Complexity: O(1)

Node *rotate(Node *head, int k) {
    if (head == NULL || head->next == NULL || k == 0) {
        // if only one node is there or k = 0 or linkedlist is empty, return the head.
        return head;
    }

    int len = 1;
    Node *temp = head;

    while (temp->next != NULL) { // find the length of LL & reach at last node.
        len++;
        temp = temp->next;
    }

    temp->next = head; // make the next of last node to head, to make circular LL.

    temp = head; // Now again start with head.

    if (k >= len) { // if k == len or k > len, take mod of k with len.
        k = k % len;
    }

    int count = 1;
    while (count < len-k) { // now go to the prev of new head.
        count++;
        temp = temp->next;
    }

    head = temp->next; // make the next of prev as new head.
    temp->next = NULL; // and add null to the next of prev.

    return head;
}