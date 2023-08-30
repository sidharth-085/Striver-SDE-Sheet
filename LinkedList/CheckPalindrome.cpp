#include <iostream>
#include <vector>
#include <stack>
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

// Approach 1: Using vector and checking the vector is it palindrome or not

// Time Complexity: O(N)
// Space Complexity: O(N)
// N is length of linkedlist

bool isPalindrome(Node *head) {
    if (head == NULL) {
        return true;
    }
    vector<int> arr;

    Node *temp = head;

    while (temp != NULL) {
        arr.push_back(temp->data); // add the data of linkedlist to arr
        temp = temp->next;
    }

    int n = arr.size();

    for (int i=0; i<=(n-1)/2; i++) { // check is arr is palindrome or not.
        if (arr[i] != arr[n-i-1]) {
            return false;
        }
    }
    return true;
}

// Approach 2: Using Stack to check reversal
// Time Complexity: O(N)
// Space Complexity: O(N)

bool isPalindrome(Node *head) {
    if (head == NULL || head->next == NULL) {
        return true;
    }

    stack<int> st;
    Node *temp = head;

    while (temp != NULL) {
        st.push(temp->data);
        temp = temp->next;
    }

    temp = head;

    while (temp != NULL) {
        int top = st.top();
        st.pop();

        if (top != temp->data) {
            return false;
        }
        temp = temp->next;
    }

    return true;
}

// Approach 3: Clone Linkedlist
// Time Complexity: O(N)
// Space Compexity: O(N)

bool isPalindrome(Node *head) {
    // Creating a temporary node.
    Node *temp = head;
    // Creating Node for storing head of reverse cloned LinkedList.
    Node *prev = NULL;
    while (temp != NULL) {
        Node *newNode = new Node(temp->data);
        newNode->next = prev;
        prev = newNode;
        temp = temp->next;
    }

    // Iterating clone and given Linked List.
    while (head != NULL) {

        // Check if both node value is same or not.
        if (head->data != prev->data) {
            return false;
        }

        head = head->next;
        prev = prev->next;

    }
    return true;
}

// Using Slow-fast Pointer & dividing first and second half
// Time Complexity: O(N)
// Space Complexity: O(1)

Node *reverse(Node *head) {
    Node *prev = NULL;
    Node *current = head;

    while (current != NULL) {
        Node *currentNext = current->next;
        current->next = prev;
        prev = current;
        current = currentNext;
    }
    return prev;
}

bool isPalindrome(Node *head) {
    if (head == NULL || head->next == NULL) {
        return true;
    }
    Node *slow = head;
    Node *fast = head;
    Node *prev = head;

    // Find the middle node using TORTOISE-HARE-APPROACH.
    while (fast != NULL && fast->next != NULL) {
        prev = slow;
        fast = fast->next->next;
        slow = slow->next;
    }

    /*
        Fast pointer would become NULL when there are even elements in the list and
        not NULL for odd elements. We need to skip the middle node for odd case.
    */
    if (fast != NULL) {
        slow = slow->next;
    }
    
    // Dividing Linked LIst in two part by pointing prev next to NULL.
    prev->next = NULL;

    // Now reverse the second half.
    Node *reverseHead = reverse(slow);

    // Iterate through both LinkedList and then compare it.
    while (head != NULL) {

        if (head->data != reverseHead->data) {
            return false;
        }
        reverseHead = reverseHead->next;
        head = head->next;

    }
    return true;
}