#include <vector>
using namespace std;

// Recursive Way: This problem is similar to Combinational Sum 1 && Subset sum to K
// Pattern: Include or not include

// Time Complexity: O(2^N) {It creates all subsets and find}

long countWaysToMakeChange(int *denominations, int si, int n, int value) {
    // if value becomes 0 means we found 1 way.
    if (value == 0) {
        return 1;
    }
    
    // if value is not equal to zero and we reached at end, we dont get any way.
    if (si == n) {
        return 0;
    }

    long include = 0; // first include if current denomination is less than value

    if (denominations[si] <= value) {
        include = countWaysToMakeChange(denominations, si, n, value - denominations[si]);
    }

    long exclude = countWaysToMakeChange(denominations, si+1, n, value);

    return include + exclude;
}

long countWaysToMakeChange(int *denominations, int n, int value) {
    return countWaysToMakeChange(denominations, 0, n, value);
}

// Memoization Approach:

// Time Complexity: O(N*Value)
// Space Complexity: O(N*Value)

long countWaysToMakeChange(int *denominations, int n, int value, vector<vector<long>> &ans) {
    if (value == 0) {
        return 1;
    }

    if (ans[n][value] != -1) {
        return ans[n][value];
    }

    long include = 0;

    if (denominations[n-1] <= value) {
        include = countWaysToMakeChange(denominations, n, value - denominations[n-1], ans);
    }

    long exclude = countWaysToMakeChange(denominations, n-1, value, ans);

    ans[n][value] = include + exclude;

    return ans[n][value];
}

long countWaysToMakeChange(int *denominations, int n, int value) {
    vector<vector<long>> ans(n+1, vector<long>(value+1, -1));
    return countWaysToMakeChange(denominations, n, value, ans);
}

// Iterative DP approach: 

// Time Complexity: O(N*Value)
// Space Complexity: O(N*Value)

long countWaysToMakeChange(int *denominations, int n, int value) {
    vector<vector<long>> ans(n+1, vector<long>(value+1));

    for (int i=0; i<=n; i++) {
        ans[i][0] = 1;
    }

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=value; j++) {
            int include = 0;
            if (denominations[i-1] <= j) { // check for include 
                include = ans[i][j - denominations[i-1]];
                // keep n same and include the current denomination by subtracting
            }
            int exclude = ans[i-1][j]; // not include (decrease n and value is same)

            ans[i][j] = include + exclude; // total ways
        }
    }
    return ans[n][value];
}
