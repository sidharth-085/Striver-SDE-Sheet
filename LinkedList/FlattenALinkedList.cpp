#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Node {
    public:
    int data;
    Node *next;
    Node *child;

    Node (int data) {
        this->data = data;
        child = NULL;
        next = NULL;
    }
};

// Brute Force Approach using Sort Function
// Time Complexity: O(n * k * Log(n * k))
// Space Complexity: O(n*k)

Node* flattenLinkedList(Node* root) {
	vector<int> answer ;
	// Traverse the linkedlist and add all the nodes to the array
	while (root != NULL) {
		Node *temp = root;
		// Add all child nodes
		while (temp != NULL) {
			answer.push_back(temp->data);
			temp = temp->child;
		}
		root = root->next;
	}

	sort(answer.begin(), answer.end());

	Node *head = NULL;
	Node *temp = NULL;

	// Create new linked list
	for (int i = 0; i < answer.size(); i++) {
		Node *newNode = new Node(answer[i]);
		if (head == NULL) {
			head = newNode;
		} 
		else {
			temp->child = newNode;
		}
		temp = newNode;
	}
	return head;
}

// Approach 2 using Merge Two Sorted LL : IN-PLACE

// Time Complexity: O(N*N*K)
// Merge function takes O(k) T.C where k is avg number of child nodes

// And we, are merging every 2 nodes of next pointer so we need to do N*N work.

Node* mergeTwoLinkedLists(Node* head1, Node* head2) {
    if (head1 == NULL) {
        return head2;
    }
    if (head2 == NULL) {
        return head1;
    }

    Node* head = nullptr;
    if (head1->data < head2->data) {
        head = head1;
        head->child = mergeTwoLinkedLists(head1->child, head2);
    } else {
        head = head2;
        head->child = mergeTwoLinkedLists(head1, head2->child);
    }
    return head;
}

// Iterative Approach of above mergeTwoLinkedLists function

Node* mergeTwoLinkedLists(Node* head1, Node* head2) {
    Node *newHead = NULL;
    Node *temp = NULL;

    while (head1 != NULL && head2 != NULL) {
        if (head1->data < head2->data) {
            if (newHead == NULL) {
                newHead = head1;
                temp = newHead;
            }
            else {
                temp->child = head1;
                temp = temp->child;
            }
            head1 = head1->child;
        }
        else {
            if (newHead == NULL) {
                newHead = head2;
                temp = newHead;
            }
            else {
                temp->child = head2;
                temp = temp->child;
            }
            head2 = head2->child;
        }
    }

    if (head1 != NULL) {
        temp->child = head1;
    }
    if (head2 != NULL) {
        temp->child = head2;
    }
    return newHead;
}

Node* flattenLinkedList(Node* head) {
    if (head == NULL || head->next == NULL) {
        return head; // Base case: Already a single-level list
    }

    Node* newLL = flattenLinkedList(head->next);
    head->next = nullptr;

    return mergeTwoLinkedLists(head, newLL);
}