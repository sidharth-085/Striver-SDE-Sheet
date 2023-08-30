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

int findLength(Node *head) {
    int count = 0;
    Node *temp = head;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}

Node *findMiddle(Node *head) {
    int midLen = findLength(head)/2;

    Node *temp = head;

    while (midLen--) {
        temp = temp->next;
    }

    return temp;
}