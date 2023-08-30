#include <iostream>
using namespace std;

// Question: find nth root of m i.e. m ^ (1/n).
// we can say that if ans = m ^ (1/n). Then, m = ans ^ n;
// so, we can multiply any number from 1 to m, n times to get the answer

// Approach 1: Brute Force Method
// Time Complexity: O(N * M)
// Space Complexity: O(1)

int nthRoot(int n, int m) {
    for (int i = 1; i <= m; i++) {
        long long ans = 1; // variable to store product and check is the product same as m

        for (int j = 1; j <= n; j++) {
            ans = ans * i; // multiply i, n times
        }

        if (ans == 1LL * m) { // if ans same as m, means i is the answer
            return i;
        }
    }

    return -1; // if not found or n or m is not within limits, return -1.
}

// Approach 2: Binary Search
// Time Complexity: O(N * Log M)
// Space Complexity: O(1)

int NthRoot(int n, int m) {
    int start = 1; // we can use binary search from 1 to m (sorted)
    int end = m;

    while (start <= end) {
        int mid = start + (end - start)/2;

        long long ans = 1;
        for (int i = 1; i <= n; i++) {
            ans = ans * mid;

            if (ans > 1LL * m) {
                break;
            }
        }

        if (ans == 1LL * m) {
            return mid;
        }
        else if (ans > m) {
            end = mid - 1;
        }
        else {
            start = mid + 1;
        }
    }

    return -1;
}