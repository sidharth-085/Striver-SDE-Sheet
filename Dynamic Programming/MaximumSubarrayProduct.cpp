#include <iostream>
#include <vector>
using namespace std;

const int mod = 1e9 + 7;

// This problem is similar to Kadane Algorithm.
// Brute Force Approach: We consider all subarrays and try to get the maximum product.

// Time Complexity: O(N^3)
// Space Complexity: O(1)

int maximumProduct(vector<int>& arr, int n) {
    long long maxProduct = INT_MIN;

    for (int i=0; i<n; i++) {
        for (int j=i; j<n; j++) {
            long long currProduct = 1;

            for (int k = i; k<=j; k++) { // calculates product for all subarrays from i to j
                currProduct = (currProduct * arr[k]) % mod; // take mod to keep values within integer
                maxProduct = max(maxProduct, currProduct);
            }

        }
    }
    return (int)(maxProduct % mod); // typecast final answer into integer
}

// Optimized Brute Force: Remove loop from i to j, instead keep the track of prev subarray product

int maximumProduct(vector<int>& arr, int n) {
    long long maxProduct = INT_MIN;

    for (int i=0; i<n; i++) {
        long long prevProduct = 1; // it just keeps track of prev subarray product
        for (int j=i; j<n; j++) { 
            prevProduct = (prevProduct * arr[j]) % mod;
            maxProduct = max(maxProduct, prevProduct);
        }
    }

    return (int)(maxProduct % mod);
}

// The Most optimal solution is traversal two sides to handle the positive & negative 
// values cases

// Time Complexity: O(N)
// Space Complexity: O(1)

int maximumProduct(vector<int>& arr, int n) {
    // we will traverse the array two times: left to right & right to left

    // left to right traversal

    long long currProduct = 1;
    long long maxProduct = LLONG_MIN;

    for (int i=0; i<n; i++) {
        currProduct = (currProduct * arr[i]) % mod;
        maxProduct = max(maxProduct, currProduct);

        if (arr[i] == 0) {
            currProduct = 1;
        }
    }

    // Now, right to left traversal to handle negative cases

    currProduct = 1;
    
    for (int i = n-1; i >= 0; i--) {
        currProduct = (currProduct * arr[i]) % mod;
        maxProduct = max(maxProduct, currProduct);

        if (arr[i] == 0) {
            currProduct = 1;
        }
    }

    return (int)(maxProduct % mod);
}