#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// Next smaller element is the element in right of the current element which is just 
// smaller than current Element

// Brute Force Approach: Nested Loops

// Time Complexity: O(N*N)
// Space Complexity: O(1)

vector<int> nextSmallerElement(vector<int> &arr, int n) {
    vector<int> ans; 

    for (int i=0; i<n; i++) {
        int curr = arr[i];

        int rightIndex = i + 1;
        // start the traversal from one ahead from current index

        // traverse the loop until we found the element which is smaller than current
        // element
        while (rightIndex < n && curr <= arr[rightIndex]) {
            rightIndex++;
        }

        // if rightIndex becomes n, means all the element at the right are greater
        // than current element

        if (rightIndex == n) {
            ans[i] = -1;
        } 

        // if rightIndex is not n, it means it is the element which is next smaller
        // for current element
        
        else {
            ans[i] = arr[rightIndex];
        }
    }

    return ans;
}

// Optimal Approach: Using Stack and traversing from last to first

// Time Complexity: O(N)
// Space Complexity: O(N)

vector<int> nextSmallerElement(vector<int>& arr, int n) {
    vector<int> ans(n);

    // Defining the stack for reverse traversal
    stack <int> stk;

    // Iterating through all the array elements from backwards.
    for (int i = n - 1; i >= 0; i--) {
        // Removing all the elements greater than or equal to current element 
        // from the stack.

        while (stk.empty() == false && arr[stk.top()] >= arr[i]) {
            stk.pop();
        }

        // if stack becomes empty, means all the elements after current element are
        // greater so next smaller element is -1.

        if (stk.empty()) {
            ans[i] = -1;
        }

        // if stack is non empty, the current top element will be the next smallest
        // element in the right.
        else {
            ans[i] = arr[stk.top()];
        }

        // Pushing the current element into the stack.
        stk.push(i);
    }

    // Returning the final vector after all the iterations.
    return ans;
}