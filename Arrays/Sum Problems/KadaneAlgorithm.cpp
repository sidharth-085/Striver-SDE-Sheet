#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Kadane algorithm is used for calculating MAXIMUM SUBARRAY SUM

// First Brute Force approach: Find All subarrays sum and determine the maximum sum
// Time Complexity: O(N^3)
// Number of Subarrays will be n(n+1)/2 and we are calculating sum for each.

long long maxSubarraySum(int *arr, int n) {
    // first calculate all subarrays and store them into one vector
    long long maxSum = INT_MIN;

    for (int i=0; i<n; i++) {
        for (int j=i; j<n; j++) {
            long long currSubarrSum = 0;
            for (int k=i; k<=j; k++) { // loop for subarray from i to j
                currSubarrSum = currSubarrSum + arr[k]; // sum for curr sub array.
            }
            maxSum = max(maxSum, currSubarrSum);
        }
    }

    if (maxSum < 0) {
        return 0;
    }
    return maxSum;
}

// Better Solution: We can just use the prev subarray sum to calculate next subarray sum
// Time Complexity: O(N^2) due to deleting one loop

long long maxSubarraySum(int *arr, int n) {
    // first calculate all subarrays and store them into one vector
    long long maxSum = INT_MIN;

    for (int i=0; i<n; i++) {
        long long prevSubarraySum = 0;
        for (int j=i; j<n; j++) {
            prevSubarraySum = prevSubarraySum + arr[j];
            // this just calculates the current subarray sum from prev subarray sum
            maxSum = max(maxSum, prevSubarraySum);
        }
    }

    if (maxSum < 0) {
        return 0;
    }
    return maxSum;
}

// Better approach can be done by using DP

/*
    Time Complexity: O(N)
    Space Complexity: O(N)

    where N is the length of the array.
*/

long long maxSubarraySum(int arr[], int n) {
    long long curSum[n]; // this dp array will store the current maximum sum till ith index.
    long long maxSum = 0;

    for(int i=0; i<n; i++) {
        if(i == 0) {
            curSum[i] = max(0, arr[i]); // if arr[i] is negative, make the first element 0.
        }
        else {
            curSum[i] = max((long long)0, curSum[i-1] + arr[i]);   
            // then update the dp array by using prev maximum subarray sum + current element. 
        }
    
        maxSum = max(maxSum, curSum[i]);
        // finally update the max sum with current sum if current sum > max sum.
    }

    return maxSum;
}

// The Optimal Solution is Kadane Algorithm
// Time Complexity: O(N)
// Space Complexity: O(1)

long long maxSubarraySum(int *arr, int n) {
    // the process is just simple, keep and maxSum & currSum 
    // if adding the current element makes currSum < 0, we make currSum = 0
    // because we only need positive sum to be carried out throughout the traversal.

    long long maxSum = LONG_MIN;
    long long currSum = 0;

    for (int i=0; i<n; i++) {
        currSum = currSum + arr[i];
        maxSum = max(maxSum, currSum); // check if currSum is greater than maxSum
        if (currSum < 0) {
            currSum = 0; // if currSum < 0, currSum = 0.
        }
        if (maxSum < 0) { // and if maxSum is negative, also make maxSum = 0.
            maxSum = 0;
        }
    }
    return maxSum;
}

// If anyone asks to get the subarray have maximum sum, we can just modify this code
// Time Complexity: O(N)
// Space Complexity: O(1)

long long maxSubarraySum(int *arr, int n) {
    long long maxSum = INT_MIN;
    long long currSum = 0;

    int ansStart = -1;
    int ansEnd = -1;
    int start = -1;

    for (int i=0; i<n; i++) {
        if (currSum == 0) {
            start = i;
        }
        currSum = currSum + arr[i];

        ansStart = start; // from this
        ansEnd = i; // to this we get subarray which has maximim sum

        maxSum = max(maxSum, currSum);

        if (currSum < 0) {
            currSum = 0;
        }
        if (maxSum < 0) {
            maxSum = 0;
        }
    }

    return maxSum;
}