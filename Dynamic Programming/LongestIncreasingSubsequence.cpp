#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Recursive Approach finds all subsequences
// Time Complexity: O(2^N)

int lisHelper(int *input, int size, int prev, int si) {
    if (si == size) {
        return 0;
    }

    // first include the element
    int taken = 0;
    if (input[si] > prev) {
        taken = lisHelper(input, size, input[si], si+1) + 1;
    }
    // it will find all subsequences and check for the maximum ans.

    // dont include the element

    int notTaken = lisHelper(input, size, prev, si+1);

    return max(taken, notTaken);
}

int longestIncreasingSubsequence(int* input, int size) {
    return lisHelper(input, size, INT_MIN, 0);
}

// Memoization Approach

int lisHelper(int *input, int size, int prev, int si, vector<vector<int>> &ans) {
    if (si == size) {
        return 0;
    }

    if (ans[si][prev+1] != -1) {
        return ans[si][prev+1];
    }
 
    // first include the element
    int taken = 0;
    if (input[si] > input[prev]) {
        taken = lisHelper(input, size, si, si+1, ans) + 1;
    }
    // it will find all subsequences and check for the maximum ans.

    // dont include the element

    int notTaken = lisHelper(input, size, prev, si+1, ans);
    
    ans[si][prev+1] = max(taken, notTaken);
    return ans[si][prev+1];
}

int longestIncreasingSubsequence(int* input, int size) {
    vector<vector<int>> ans(size+1, vector<int>(size+1, -1));
    return lisHelper(input, size, -1, 0, ans);
}

// NAIVE DP APPROACH
// Time Complexity: O(N^2)
// Time Complexity: O(N)

int longestIncreasingSubsequence(int* input, int size) {
    int *lis = new int[size]; // DP 1D TABLE

    lis[0] = 1; // for first number, longestIncreasingSequence can only be 1.

    int maxAns = 0;

    for (int i=1; i<size; i++) {
        lis[i] = 1;
        for (int j=i-1; j>=0; j--) { 

            // traverse from last to front in input arr.

            if (input[j] > input[i]) { 

                // if prev element is bigger, then skip and go to next.

                int possibleAns = 1 + lis[j];

                if (possibleAns > lis[i]) {
                    lis[i] = possibleAns;
                }
            }
        }
        maxAns = max(maxAns, lis[i]);
    }

    return maxAns;
}

// Approach 2 using Parent-Sorting Method (Optimal DP approach)
// Time Complexity: O(N * logN)
// Space Complexity: O(N)

int longestIncreasingSubsequence(int arr[], int n) {
    if (n == 0) {
        return 0;
    }

    vector<int> lis; // lis for largest increasing subsequence
    lis.push_back(arr[0]);

    for (int i = 1; i < n; i++) {
        if (arr[i] > lis[lis.size() - 1]) { // if the current element is bigger, push in LIS
            lis.push_back(arr[i]);
        } 
        else { // if current element is smaller, then replace the just greater than or 
              //  equal to element to current element.
            auto it = lower_bound(lis.begin(), lis.end(), arr[i]);
            // lower bounds returns an iterator
            *it = arr[i];
        }
    }

    return lis.size();
}