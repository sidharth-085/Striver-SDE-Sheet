#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <deque>
using namespace std;

// Approach 1: Brute Force Approach
// Time Complexity: O(N * N * N)
// Space Complexity: O(1)

vector<int> maxMinWindow(vector<int> arr, int n) {
    vector<int> ans;

    // Iterate through all possible starting points of the window
    for (int i = 0; i < n; i++) {
        // Iterate through all possible ending points of the window
        for (int j = i; j < n; j++) {
            // Define the start and end indices of the current window
            int start = i;
            int end = j;

            // Initialize a variable to store the minimum value within the window
            int mini = INT_MAX;

            // Find the minimum value within the current window
            for (int k = start; k <= end; k++) {
                mini = min(mini, arr[k]);
            }

            // Calculate the length of the current window
            int length = end - start + 1;

            // Update the answer array with the maximum of the current minimum value
            // for the corresponding window length
            ans[length - 1] = max(ans[length - 1], mini);
        }
    }
    
    return ans;
}

// Approach 2: Better Approach using Map
// Time Complexity: O(N * N * Log N)
// Space Complexity: O(K)

vector<int> maxMinWindow(vector<int> arr, int n) {
    vector<int> ans;

    // Iterate through different window lengths (k)
    for (int k = 1; k <= n; k++) {
        int maxi = INT_MIN;  
        // Initialize the maximum value for the current window length

        map<int, int> minMap;  
        // Create a map to track the frequency of elements within the window

        // Populate the frequency map for the initial window of size k
        for (int i = 0; i < k; i++) {
            minMap[arr[i]]++;  
        }

        // Find the maximum element within the current window
        int minElement = minMap.begin()->first;
        maxi = max(maxi, minElement);

        int j = 0;  
        // Initialize a pointer to the start of the previous window

        // Slide the window over the array
        for (int i = k; i < n; i++) {
            // Decrease the frequency of the element that is leaving the window
            minMap[arr[j]]--;

            // If the frequency becomes zero, remove the element from the map
            if (minMap[arr[j]] == 0) {
                minMap.erase(arr[j]);
            }

            // Add the new element to the frequency map
            minMap[arr[i]]++;

            // Find the minimum element within the updated window, which is at 
            // front of the map

            int minElement = minMap.begin()->first;
            maxi = max(maxi, minElement);

            // now update the maxi which stores the maximum value for diff current 
            // window by taking maximum of minElement for current window of size k

            j++;  
            // Move the window's start pointer to the right
        }

        ans.push_back(maxi);
    }

    return ans;
}

// Approach 3: Using Deque by sliding on every Window
// Time Complexity: O(N * N)
// Space Complexity: O(K)

vector<int> maxMinWindow(vector<int> arr, int n) {
    vector<int> ans;

    // Iterate through different window lengths (k)
    for (int k = 1; k <= n; k++) {
        int maxi = INT_MIN;  

        deque<int> dq; 
         // Create a deque to store indices of elements in the current window
        
        // Process the first k elements to populate the deque
        for (int i = 0; i < k; i++) {
            // Remove elements from the back of the deque that are smaller than or 
            // equal to arr[i] to keep the element in the increasing order

            while (!dq.empty() && arr[i] <= arr[dq.back()]) {
                dq.pop_back();
            }

            dq.push_back(i);  // Add the current index to the deque
        }

        // The front element of the deque contains the index of the minimum element 
        // in the window and we are taking the maximum with maxi as said in ques

        maxi = max(maxi, arr[dq.front()]);

        int j = 0;  // Initialize a pointer to the start of the previous window

        for (int i = k; i < n; i++) {
            // Remove elements from the front of the deque that are outside of the 
            // current window

            while (!dq.empty() && dq.front() <= j) {
                dq.pop_front();
            }

            // Remove elements from the back of the deque that are smaller than or 
            // equal to arr[i] to maintain the increasing order

            while (!dq.empty() && arr[i] <= arr[dq.back()]) {
                dq.pop_back();
            }

            dq.push_back(i);  // Add the current index to the deque

            maxi = max(maxi, arr[dq.front()]);  
            // Update the maximum value for the current window with minimum value 
            // for current window of size k

            j++;  
            // Move the window's start pointer to the right
        }

        // Store the maximum element found in the current window length
        ans.push_back(maxi);
    }

    return ans;
}

// Approach 4: Optimal Approach
// Time Complexity: O(N)
// Space Complexity: O(N)

// This function finds previous smaller element index of current element, same as Previous
// smaller element Problem

vector<int> prevSmallerIndices(vector<int> &arr, int n) {
    vector<int> ans(n);

    stack<int> stk;

    for (int i=0; i<n; i++) {
        while (stk.empty() == false && arr[stk.top()] >= arr[i]) {
            stk.pop();
        }

        if (stk.empty()) {
            ans[i] = -1;
        }
        else {
            ans[i] = stk.top();
            // it stores the index of the previous smaller element
        }

        stk.push(i);
    }

    return ans;
}

// This function finds next smaller element index of current element, same as Next
// smaller element Problem

vector<int> nextSmallerIndices(vector<int> &arr, int n) {
    vector<int> ans(n);

    stack<int> stk;

    for (int i=n-1; i>=0; i--) {
        while (stk.empty() == false && arr[stk.top()] >= arr[i]) {
            stk.pop();
        }

        if (stk.empty()) {
            ans[i] = n;
        }
        else {
            ans[i] = stk.top();
            // it stores the index of the next smaller element
        }

        stk.push(i);
    }

    return ans;
}

vector<int> maxMinWindow(vector<int> arr, int n) {
    // step 1: create an ans array which has every element INT_MIN
    vector<int> ans(n, INT_MIN);

    // step 2: find the previous smaller element and next smaller element indices
    // to find the size of the window by making arr[i] as minimum element in the current
    // window

    vector<int> prevSmaller = prevSmallerIndices(arr, n);

    vector<int> nextSmaller = nextSmallerIndices(arr, n);

    // step 3: traverse the complete array and find the length of the window using 
    // previous smaller and next smaller indices

    for (int i=0; i<n; i++) {
        // find the length of the window in which arr[i] is minimum becuase before
        // next smaller index, all the elements are greater than arr[i] and after the 
        // previous smaller element, all the elements are greater than arr[i]

        int length = nextSmaller[i] - prevSmaller[i] - 1;
        // same as width for Largest Area of Histogram

        ans[length - 1] = max(ans[length- 1], arr[i]);
        // take the maximum for different values of minimum for current window length

        // ith index represents i+1 size of window, so for current length, one should
        // be minus.
    }

    // step 4: at last, some windows are left and left unfilled, fill those windows
    // using next size of window

    for (int i = n-2; i >= 0; i--) {
        ans[i] = max(ans[i], ans[i+1]);
    }

    return ans;
}   