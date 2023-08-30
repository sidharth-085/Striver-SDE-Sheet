#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// Approach 1: Brute Force Approach
// Time Complexity: O(N * N)
// Space Complexity: O(1)

int maxSumSlidingWindow(vector<int> &arr, int k) {
    int maxSum = INT_MIN;

    int n = arr.size();

    for (int i=0; i<n-k+1; i++) { // run the loop for every window
        int sum = 0;
        for (int j=i; j<i+k; j++) { // for every window, find the sum and maximize 
            sum = sum + arr[j];
        }

        maxSum = max(maxSum, sum);
    }

    return maxSum;
}

// Approach 2: Using Sliding Window Approach
// Time Complexity: O(N)
// Space Complexity: O(1)

int maxSumSlidingWindow(vector<int> &arr, int k) {
    int n = arr.size();

    int maxSum = INT_MIN;
    // maximum sum is INT_MIN, we can take it 0 also.

    int sum = 0;
    // current sum is zero initially

    for (int i=0; i<k; i++) { // find the sum for the first window
        sum = sum + arr[i];
    }

    // check is current sum is bigger than maximum sum or not.

    maxSum = max(maxSum, sum);

    int j = 0;
    // pointer for starting element of previous window to be remove.

    for (int i=k; i<n; i++) {
        sum = sum - arr[j]; // first exclude the previous window element i.e. arr[j]

        sum = sum + arr[i]; // add the current window last element to the sum

        maxSum = max(maxSum, sum);
        // now maximize the maxSum if sum is bigger than maxSum

        j++;
        // finally move the starting pointer of previous window ahead
    }

    return maxSum;
}