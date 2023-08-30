#include <iostream>
#include <stack>
using namespace std;

// Approach 1: Using Two Stack Approach (Costly enqueue)
// Time Complexity: O(N * Q) (for push Q queries)
// Space Complexity: O(N)

class Queue {
    stack<int> stk; // main stack
    stack<int> extra; 
    // extra stack for storing existing elements and put back to main stack
    
    public:

    void enQueue(int val) {
        // first check is main stack is empty, if empty, append the val and return.
        if (stk.empty()) {
            stk.push(val);
            return;
        }

        // first pop out all the existing elements of main stack and store in 
        // extra stack

        while (stk.empty() == false) {
            extra.push(stk.top());
            stk.pop();
        }

        // then add the val to the main stack at the end

        stk.push(val);

        // and then finally add back all the elements to the main stack

        while (extra.empty() == false) {
            stk.push(extra.top());
            extra.pop();
        }
    }

    int deQueue() {
        if (stk.empty()) { // if stack is empty, return -1 for dequeue
            return -1;
        }

        int top = stk.top(); // pop out the first element and return
        stk.pop();

        return top;
    }

    int peek() {
        if (stk.empty()) {
            return -1;
        }

        return stk.top(); // return the top element of stack
    }

    bool isEmpty() {
        return stk.size() == 0; // return is stack is empty or not
    }
};

// Approach 2: Two Stack Approach (Costly dequeue)
// Time Complexity: O(N*Q) (for popping and getting peak element Q queries)
// Space Complexity: O(N)

class Queue {
    stack<int> stk; // main stack
    stack<int> extra; 
    // extra stack for storing existing elements and put back to main stack
    
    public:

    void enQueue(int val) {
        stk.push(val);
    }

    int deQueue() {
        if (stk.empty()) { // if stack is empty, return -1 for dequeue
            return -1;
        }

        // first reverse the stk using extra stack and make stk empty

        while (stk.empty() == false) {
            extra.push(stk.top());
            stk.pop();
        }

        // then take out the top node which is top element of queue and pop it from
        // extra stack

        int top = extra.top();
        extra.pop();

        // finally push all the elements of extra stack to stk

        while (extra.empty() == false) {
            stk.push(extra.top());
            extra.pop();
        }

        // return the popped element

        return top;
    }

    int peek() {
        if (stk.empty()) {
            return -1;
        }

        // for peek element, first empty the stk and put in extra stack

        while (stk.empty() == false) {
            extra.push(stk.top());
            stk.pop();
        }

        // take the top element of extra stack

        int top = extra.top();

        // and then revert back all the elements of extra stack to stk.

        while (extra.empty() == false) {
            stk.push(extra.top());
            extra.pop();
        }
        
        // return the top element

        return top;
    }

    bool isEmpty() {
        return stk.size() == 0; // return is stack is empty or not
    }
};

// Approach 3: Using Single Stack (space optimization using Recursion)
// Time Complexity: O(N * Q) (for peek and dequeue function, for Q queries) 
// Space Complexity: O(N)

class Queue {
    stack<int> stk;

    public:

    void enQueue(int val) {
        stk.push(val);
        // push the value in stack
    }

    int deQueue() {
        if (stk.empty()) {
            return -1;
        }

        // we are performing the recursion here, first pick out the top element and
        // store it in variable top

        int top = stk.top();
        stk.pop();

        // now check after popping out the element, is stack becomes empty, if yes
        // it means it is the last element and the last element is the first element 
        // in the queue so return top

        if (stk.empty()) {
            return top;
        }

        // if stack is non empty, we can still pop elements and check for answer
        // so call recursion and get the answer of popped element

        int popped = deQueue();

        stk.push(top);
        // backtrack and put back the popped element at first in the starting and 
        // return the first element in the queue

        return popped;
    }

    int peek() {
        if (stk.empty()) {
            return -1;
        }

        // repeat same for peek function also

        int top = stk.top();
        stk.pop();

        if (stk.empty()) {
            // if stack becomes empty after popping the element, means it is the top 
            // element. Push the popped element to the stack back and return top.

            stk.push(top);
            return top;
        }

        // then similarly to dequeue function perform recursion and get the answer

        int next = peek();

        stk.push(top);

        return next;
    }

    bool isEmpty() {
        return stk.empty();
    }
};