#include <iostream>
using namespace std;

// Pre-requiste: KRerverse.cpp

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

// Brute Force Approach: Using recursion
// Time Complexity: O(N)
// Space Complexity: O(N)

// This method applicable when question said, when block size is more than curr length
// of linkedlist, dont reverse it

Node *getListAfterReverseOperation(Node *head, int n, int *arr) {
	if (n == 0) { // if all blocks given in arr is covered, just return head.
		return head;
	}

	if (head == NULL || head->next == NULL) { 
        // if size of linkedlist is 0 or 1, return head
		return head;
	}

	if (arr[0] == 0) { // if the block in arr is 0, then skip to next block in arr.
		return getListAfterReverseOperation(head, n-1, arr+1);
	}

    Node *prev = NULL;
    Node *next = NULL;
    Node *curr = head;

    int count = 0;

    while (count < arr[0] && curr != NULL) { // reverse the LL till k
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }

    if (count < arr[0]) { 
        // it curr reaches to null means curr size of ll is less than k, dont reverse it.
        curr = prev;
        prev = NULL;
        next = NULL;
        count = 0;

        while (count < arr[0] && curr != NULL) { 
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
            count++;
        }
    }

	if (next != NULL) {
		head->next = getListAfterReverseOperation(next, n-1, arr+1);
	}

	return prev;
}

// This method applicables when question said reverse the remaining part even if 
// block size is bigger than current size of linkedlist

Node *getListAfterReverseOperation(Node *head, int n, int *arr) {
	if (n == 0) { // if all blocks given in arr is covered, just return head.
		return head;
	}

	if (head == NULL || head->next == NULL) { 
        // if size of linkedlist is 0 or 1, return head
		return head;
	}

	if (arr[0] == 0) { // if the block in arr is 0, then skip to next block in arr.
		return getListAfterReverseOperation(head, n-1, arr+1);
	}

	int count = 0;

	Node *next = NULL;
	Node *prev = NULL;
	Node *curr = head;

	while (count < arr[0] && curr != NULL) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
		
		count++;
	}
    // it will reverse the linkedlist even if block size is greater.
    // to avoid this, we can check length of current linkedlist.

	if (next != NULL) {
		head->next = getListAfterReverseOperation(next, n-1, arr+1);
	}

	return prev;
}

// Optimal Approach: Using Iterative Method
// Time Complexity: O(N)
// Space Complexity: O(1)

// This method applicables when question said reverse the remaining part even if 
// block size is bigger than current size of linkedlist

Node *getListAfterReverseOperation(Node *head, int n, int *arr) {
    if (head == NULL) {
        return NULL;
    }
    
    int index = 0;

    Node *curr = head;
    Node *prev = NULL;
    Node *next = NULL;

    Node *newHead = NULL;
    Node *tail = NULL;
    Node *join = NULL;

    while (curr != NULL && index < n) {
        int k = arr[index];

        if (k == 0) { // if block size is 0, skip it.
            index++;
            continue;
        }

        prev = NULL;
        join = curr;
        int count = 0;

        while (count < k && curr != NULL) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
            count++;
        }

        if (newHead == NULL) { // if newHead is not updated, update it
            newHead = prev;
        }

        if (tail != NULL) {
            tail->next = prev;
        }

        tail = join;
        index++;
    }

    if (tail != NULL) { // if we iterted complete blocks, attach remaining linkedlist.
        tail->next = curr;
    }

    if (newHead == NULL) { // if newHead is NULL, doesn't change the list, return head.
        return head;
    }

    return newHead; // else return newHead.
}