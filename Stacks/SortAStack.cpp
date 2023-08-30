#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Approach 1: Using Recursion
// Time Complexity: O(N^2)
// Space Complexity: O(N)

// we will use the similar approach we have done in insertion sort, first we pop the 
// top element and sort the remaining stack. After sorting of remaining stack, we
// insert the popped element in correct position

void sortedStackInsert(stack<int> &stk, int element) {
    // step 1: check base case, if stack is empty or element is bigger than top 
    // element of stack, insert the element in stack

    if (stk.empty() || element > stk.top()) {
        stk.push(element);
        return;
    }

    // step 2: if stack is not empty and element is smaller than current top element 
    // of stack, pop the first element and try for remaining stack

    int top = stk.top();
    stk.pop();

    sortedStackInsert(stk, element);

    // step 3: now, the element is inserted in its correct position we can insert back
    // the topmost element in stack because it was greatest

    stk.push(top);
}

void sortStack(stack<int> &stk) {
    // step 1: check the base case

    if (stk.empty()) {
        return;
    }

    // step 2: Pop the top element and sort the remaining stack

    int top = stk.top();
    stk.pop();

    sortStack(stk);

    // step 3: after sorting the remaining stack insert the top element in sorted stack.

    sortedStackInsert(stk, top);
}

// Approach 2: Copy elements of stack into vector. Sort the vector and copy back to stack
// Time Complexity: O(N)
// Space Complexity: O(N)

void sortStack(stack<int> &stack) {
	vector<int> ans;

	while (!stack.empty()) {
		ans.push_back(stack.top());
		stack.pop();
	}

	sort(ans.begin(), ans.end());

	for (int i=0; i<ans.size(); i++) {
		stack.push(ans[i]);
	}
}