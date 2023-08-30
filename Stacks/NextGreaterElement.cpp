#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// This question is similar to Next smaller element in an array.
// Next greater element is the element which lies right of the current element and 
// just greater than the current element

// Brute Force Approach: Using nested loops and traverse the array

// Time Complexity: O(N*N)
// Space Complexity: O(1)

vector<int> nextGreater(vector<int> &arr, int n) {
    vector<int> ans(n);

    for (int i = 0; i < n; i++) {
        int curr = arr[i];

        int rightIndex = i + 1;
        // start the traversal from one ahead from current index

        // traverse the loop until we found the element which is greater than current
        // element

        while (rightIndex < n && curr >= arr[rightIndex]) {
            rightIndex++;
        }

        // if rightIndex becomes n, means all the element at the right are smaller
        // than current element

        if (rightIndex == n) {
            ans[i] = -1;
        } 

        // if rightIndex is not n, it means it is the element which is next greater
        // for current element
        
        else {
            ans[i] = arr[rightIndex];
        }
    }

    return ans;
}

// Optimal Approach: Using Stacks and traversing from end

// Time Complexity: O(N)
// Space Complexity: O(N)

vector<int> nextGreater(vector<int> &arr, int n) {
    vector<int> ans(n); // make the answer vector

    stack<int> stk; // stack to traverse in reverse direction.

    for (int i=n-1; i>=0; i--) {
        while (stk.empty() == false && arr[stk.top()] <= arr[i]) {
            // remove elements which are smaller than arr[i] because we want just large
            // element than arr[i]

            stk.pop();
        }

        // if stack becomes empty, means all the element after current elements are
        // smaller, then the next greater is -1

        if (stk.empty()) {
            ans[i] = -1;
        }

        // if stack is non empty, top element is the greater element than arr[i]
        else {
            ans[i] = arr[stk.top()];
        }

        stk.push(arr[i]); // at the end just push current index in stack for next
        // iteration.
    }

    return ans;
}