#include <iostream>
#include <stack>
using namespace std;

// Approach using 2 Stack: One for all elements and one for minimum elements
// Time Complexity: O(N)
// Space Complexity: O(N)

// N is number of operations

class minStack {
    stack<int> mainStk; // main stack
    stack<int> minStk; // stack for storing minimum elements
 
    public:

    void push(int num) {
        mainStk.push(num); // push element in main stack

        if (minStk.empty() || num <= minStk.top()) { 
            // if min stack is empty or current num is less than top element of 
            // min stack push it.

            minStk.push(num);
        }
    }

    int pop() {
        if (mainStk.empty()) {
            return -1;
        }

        // if current min stack is non empty and the top element to be popped in main
        // stack is same as minimum element so far, remove from min stack also.

        if (!minStk.empty() && mainStk.top() == minStk.top()) {
            minStk.pop();
        }

		int top = mainStk.top();

        mainStk.pop();

		return top;
    }

    int top() { 
        if (mainStk.empty()) {
            return -1;
        }

        return mainStk.top(); // return top element
    }

    int getMin() {
        if (minStk.empty()) {
            return -1;
        }

        return minStk.top(); // return minimum element
    }
};