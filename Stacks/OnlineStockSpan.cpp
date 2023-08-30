#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// Approach 1: Brute Force Method
// Time Complexity: O(N^2)
// Space Complexity: O(N)

vector<int> findSpans(vector<int> &arr) {
    int n = arr.size();
    vector<int> ans;

    for (int i = 0; i < n; i++) {
        int count = 1;  // Initialize the count for the current element

        // Iterate through previous elements to find elements greater than or equal 
        // to the current element

        for (int j = i - 1; j >= 0; j--) {
            if (arr[j] > arr[i]) {  
                // If we find a greater element, stop counting
                break;
            }
            count++;  
            // Increment the count if the element is less than or equal to the current
            // element
        }

        ans.push_back(count);  // Add the count to the answer vector
    }

    return ans;  // Return the vector containing the counts
}

// Approach 2: Optimal Approach
// Time Complexity: O(N)
// Space Complexity: O(N)

vector<int> findSpans(vector<int> &arr) {
    int n = arr.size();

    vector<int> ans;  // This vector will store the span values for each element
    stack<int> stk;    // Stack to keep track of indices of elements in the array

    for (int i = 0; i < n; i++) {
        // Keep removing indices from the stack as long as they are smaller than or 
        // equal to the current element

        while (stk.empty() == false && arr[stk.top()] <= arr[i]) {
            stk.pop();
        }

        // If the stack is empty, it means there is no greater element to the left of 
        // the current element

        if (stk.empty()) {
            ans.push_back(i + 1);  
            // The span is the index of the current element + 1
        } 
        else {
            ans.push_back(i - stk.top()); 
            // The span is the difference between the current index and the top index 
            // in the stack
        }

        stk.push(i);  // Push the current index onto the stack
    }

    return ans;  // Return the vector containing the span values
}