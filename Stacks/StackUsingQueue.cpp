#include <iostream>
#include <queue>
using namespace std;

// QUICK TIP: to understand first two appraoches, dry run on both of them.

// Approach 1: Using two inbuilt queues
// Time Complexity: O(N) {for push}
// Space Complexity: O(N) {due to another queue}

class Stack {
   public:
    queue<int> *q1, *q2; // we have to use pointers to swap between the queues

    // Constructor.
    Stack() {  
        q1 = new queue<int>();
        q2 = new queue<int>();
    }

    // Return the size of the queue 'q1'.
    int getSize() {
        return q1->size();  
    }

    bool isEmpty() {
        return getSize() == 0;
    }

    void push(int data) {
        // Enqueue new element to q2.
        q2->push(data);  

        // Enqueue all the elements of q1 into q2.
        while (q1->size() > 0) {  
            int front = q1->front();
            q2->push(front);
            q1->pop();
        }

        // Swap q1 and q2.
        queue<int> *temp = q1; // we are keeping q1 empty everytime we push an element
        q1 = q2;
        q2 = temp;
    }

    int pop() {
        // If empty, return -1.
        if (isEmpty()) {  
            return -1;
        }
        // Simply dequeue from the queue q1.
        int ans = q1->front();  
        q1->pop();
        return ans;
    }

    int top() {
        if (isEmpty()) {
            return -1;
        }

        int ans = q1->front();

        return ans;
    }
};

// Approach 2: Using 2 inbuilt queues
// Time Complexity: O(N) {for pop}
// Space Complexity: O(N) {due to another queue}

class Stack {
   public:
    queue<int> *q1, *q2;

    Stack() {  
        // Constructor.
        q1 = new queue<int>();
        q2 = new queue<int>();
    }

    int getSize() {
        // Return the size of the queue 'q1'.
        return q1->size();  
    }

    bool isEmpty() {
        return getSize() == 0;
    }

    void push(int data) {  
        // Simply enqueue data to q1.
        q1->push(data); 
    }

    int pop() { // here we switch queues during pop functions
        if (isEmpty()) {
            return -1;
        }

        // Enqueue all the elements of q1 into q2 except the last one.
        while (q1->size() > 1) {  
            q2->push(q1->front());
            q1->pop();
        }

        // Last element of q1 is our answer.
        int ans = q1->front();  // q1 is keeping empty everytime we pop an element.
        q1->pop();

        // Swap q1 and q2.
        queue<int> *temp = q1;  
        q1 = q2;
        q2 = temp;

        return ans;
    }

    int top() {
        if (isEmpty()) {
            return -1;
        }

        // Enqueue all the elements of q1 into q2 except the last one.
        while (q1->size() > 1) {  
            q2->push(q1->front());
            q1->pop();
        }

        // Last element of q1 is our answer.
        int ans = q1->front();  
        q1->pop();
        // Enqueue the top to q2.
        q2->push(ans);  

        queue<int> *temp = q1;
        q1 = q2;
        q2 = temp;

        return ans;
    }
};

// Approach 3: Using single inbuilt queue
// Time Complexity: O(N) {for push}
// Space Complexity: O(1)

class Stack {
    queue<int> q;

    public:

    int getSize() {
        return q.size();
    }

    int isEmpty() {
        return q.size() == 0;
    }

    void push(int value) {
        q.push(value);

        int count = 0;
        while (count < q.size() - 1) { 
            // shifts every element back to get stack like structure
            int front = q.front();
            q.push(front);
            q.pop();

            count++;
        }
    }

    int pop() {
        if (q.size() == 0) {
            return -1;
        }

        int value = q.front();
        q.pop();

        return value;
    }

    int top() {
        if (q.size() == 0) {
            return -1;
        }
        
        return q.front();
    }
};