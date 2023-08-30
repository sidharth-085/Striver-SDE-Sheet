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

// Approach 1: Recursion
 
Node *addTwoNumbersHelper(Node *num1, Node *num2, int carry) {
    if (num1 == NULL && num2 == NULL && carry == 0) {
        return NULL;
    }

    int data1 = (num1 == NULL) ? 0 : num1->data;
    Node *next1 = (num1 == NULL) ? NULL : num1->next;

    int data2 = (num2 == NULL) ? 0 : num2->data;
    Node *next2 = (num2 == NULL) ? NULL : num2->next;

    int sum = data1 + data2 + carry;
    carry = sum / 10;

    Node *sumNode = new Node(sum % 10);
    sumNode->next = addTwoNumbersHelper(next1, next2, sum / 10);
    
    return sumNode;
}

Node *addTwoNumbers(Node *num1, Node *num2) {
    return addTwoNumbersHelper(num1, num2, 0);
}

// Approach 2: Optimal Approach

Node *addTwoNumbers(Node *num1, Node *num2) {
    // here num1 and num2 is already given in reverse order, if not given
    // reverse the LinkedList using Reverse function

    Node *newHead = new Node(-1);
    Node *temp = newHead;

    int carry = 0;

    while (num1 != NULL || num2 != NULL || carry == 1) {
        int sum = 0;
        if (num1 != NULL) {
            sum = sum + num1->data;
            num1 = num1->next;
        }

        if (num2 != NULL) {
            sum = sum + num2->data;
            num2 = num2->next;
        }

        sum = sum + carry;
        carry = sum / 10;
        Node *newNode = new Node(sum % 10);
        temp->next = newNode;
        temp = temp->next;
    }
    return newHead->next;
}