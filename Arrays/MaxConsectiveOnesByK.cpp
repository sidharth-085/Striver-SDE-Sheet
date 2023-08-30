#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Find length of maximum consecutive 1s by switching k zeroes to one.

// Brute Force Approach: Nested Loops
// Time Complexity: O(N^2)
// Space Complexity: O(N)

int longestSubSeg(vector<int> &arr, int n, int k) {
    // step 1: traverse the array and check for 1 and 0

    int maxLen = 0;

    for (int i=0; i<n; i++) {
        int kCopy = k;
        // check is the element is 0 or not
        if (arr[i] == 0) {
            // step 2: if the current element is 0, check can we switch it to 1 or not.

            if (kCopy > 0) { // if kCopy is greater than 0, then we can switch it.
                kCopy--;
            }
            else { 
                // if we cant switch it, this subarray is not candidate for max 
                // consecutive ones.
                continue;
            }
        }

        // step 3: start traversing from ahead of i.
        int j;
        for (j=i+1; j<n; j++) {
            if (arr[j] == 0) { // if found 0, check can we switch it
                if (kCopy > 0) {
                    kCopy--;
                }
                else { // if kCopy is 0, then we should break and check for maxLen.
                    break;
                }
            }
        }

        maxLen = max(maxLen, j - i);
    }
}

// Approach 2: Using Queue to store all indices having element 0.
// Time Complexity: O(N)
// Space Complexity: O(K)

int longestSubSeg(vector<int> &arr, int n, int k) {
    // step 1: make queue for storing 0 element indices
    queue<int> q;
    int size = 0; // size of queue

    int maxLen = 0;
    int start = 0; // start index of the subarray which we have to consider

    // step 2: traverse the array and find the appropriate maxlen.

    for (int i=0; i<n; i++) {
        if (arr[i] == 0) { // push the ith index into queue if the element is 0.
            q.push(i);
            size++;
        }

        if (size > k) { // when q has more then k elements at which 0 is found
            // we have to update the the starting index of subarray which are in
            // consideration

            start = q.front() + 1;
            q.pop();

            size--;
        }

        maxLen = max(maxLen, i - start + 1);
    }

    return maxLen;
}

// Approach 3: Using Two Pointer Approach Differently
// Time Complexity: O(N)
// Space Complexity: O(1)

int longestSubSeg(vector<int> &arr, int n, int k) {
    // instead of using queue for updating the starting index, we can use 
    // two pointer approach

    int start = 0; // act as left pointer
    int countZeroes = 0;
    int maxLen = 0;

    for (int i=0; i<n; i++) { // loop for right pointer
        if (arr[i] == 0) {
            countZeroes++; // if zero is found, increase the count of zero.
        }

        while (countZeroes > k) { // when the count of zero is bigger than k
            if (arr[start] == 0) {
                countZeroes--;
            }

            start++; // move the start pointer ahead
        }

        maxLen = max(maxLen, i - start + 1); 
        // finally maximize the length of subarray of consective ones
    }

    return maxLen;
}