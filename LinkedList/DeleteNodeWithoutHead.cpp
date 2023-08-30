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

void deleteNode(Node *node) {
    node->data = node->next->data; // first copy the data of next node to current node.
    Node *temp = node->next; // now moves the node to next node.

    node->next = temp->next; // then break the connection and delete.
    temp->next = NULL;
    delete temp;
}