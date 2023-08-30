#include <iostream>
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

// Recursive Approach
// Time Complexity: O(max(N, M))
// Space Complexity: O(max(N, M))

Node* sortTwoLists(Node* first, Node* second) {
    if (first == NULL) {
        return second;
    }

    if (second == NULL) {
        return first;
    }

    Node *head = NULL;

    if (first->data < second->data) {
        head = first;
        head->next = sortTwoLists(first->next, second);
    }
    else {
        head = second;
        head->next = sortTwoLists(first, second->next);
    }

    return head;
}

// Iterative Approach
// Time Complexity: O(max(N, M))
// Space Complexity: O(1)

// N & M lengths of first & second LL.

Node* sortTwoLists(Node* first, Node* second) {
    if (first == NULL) {
        return second;
    }

    if (second == NULL) {
        return first;
    }

    Node *head = NULL;

    if (first->data < second->data) {
        head = first;
        first = first->next;
    }
    else {
        head = second;
        second = second->next;
    }

    Node *temp = head;
    
    while (first != NULL && second != NULL) {
        if (first->data < second->data) {
            temp->next = first;
            first = first->next;
        }
        else {
            temp->next = second;
            second = second->next;
        }

        temp = temp->next;
    }

    if (first != NULL) {
        temp->next = first;
    }

    if (second != NULL) {
        temp->next = second;
    }

    return head;
}