#include <iostream>
#include <stack>
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

void printReverse(Node *head) { // Print Recursive Approach
	if (head==NULL) {
		return;
	}
	printReverse(head->next);
	cout << head->data << " ";
	return;
}

Node* reverseLL(Node *head) { // Recursive approach 1
    if (head==NULL or head->next==NULL) {
        return head;
    }
    Node *smallLL = reverseLL(head->next);
    head->next->next = head;
    head->next = NULL;
    return smallLL;
}

Node* reverse(Node *head) { // recursive appraoch 2
    if (head==NULL) {
        return head;
    }
    Node *ans = reverse(head->next);
    Node *temp = ans;
    while (temp->next!=NULL) {
        temp = temp->next;
    }
    temp->next = head;
    return ans;
}

Node* reverseLinkedList(Node *head) { // Iterative Approach
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

Node* reverseLinkedList(Node *head) { // using stack approach
    if (head == NULL || head->next == NULL) {
        return head;
    }
    
    stack<Node*> s;
    Node *temp = head;

    while (temp != NULL) {
        s.push(temp);
        temp = temp->next;
    }

    Node *newHead = s.top();
    s.pop();
    temp = newHead;

    while (!s.empty()) {
        Node *top = s.top();
        s.pop();

        temp->next = top;
        temp = top;
    }
    temp->next = NULL;
    return newHead;
}