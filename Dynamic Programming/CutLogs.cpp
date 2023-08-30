#include <vector>
#include <climits>
using namespace std;

// we have k axes and n sized log stand && infinite logs to cut

// We have to find the minimum moves in which we can cut logs without breaking the axe
// means limit of axe to cut the logs

// Approach 1: Recursion
// Time Complexity: O(K ^ N)
// Space Complexity: O(K + N)

int cutLogs(int k, int n) {
    // if there is 0 or less sized log stand, no moves should be there
    if (n <= 0 || k <= 0) {
        return 0;
    }

    // if there is only one sized log stand, it means minimum moves to check the limit is 1.
    if (n == 1) {
        return 1;
    }

    // if there is only one axe, the minimum movies should be n
    if (k == 1) {
        return n;
    }
    
    int minCount = n; 
    // minimum count should be n initially because we can make n moves at max for n sized log stand
    
    for (int i=1; i<=n; i++) { // take logs one by one and try to cut them with axe
        int notPossible = cutLogs(k-1, i-1); 
        // if we swing axe and not able to cut the i log, means one axe is broken and try for one less log
        int possible = cutLogs(k, n-i);
        // if we swing axe and able to cut the log i logs, then we have all axes safe & n-i logs remaining

        int curr = max(notPossible, possible) + 1; // add one move for try to cut initially

        minCount = min(minCount, curr);
    }
    return minCount;
}

// Approach 2: Using Memoization method
// Time Complexity: O(N * N * K)
// Space Complexity: O(N*K)

int cutLogs(int k, int n, vector<vector<int>> &ans) {
    if (n <= 0 || k <= 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    if (k == 1) {
        return n;
    }
    
    if (ans[k][n] != -1) {
        return ans[k][n];
    }

    int minCount = n;
    for (int i=1; i<=n; i++) {
        int notPossible = cutLogs(k-1, i-1, ans);
        int possible = cutLogs(k, n-i, ans);

        int curr = max(notPossible, possible) + 1;

        minCount = min(minCount, curr);
    }
    ans[k][n] = minCount;
    return ans[k][n];
}

int cutLogs(int k, int n) {
    vector<vector<int>> ans(k+1, vector<int>(n+1, -1));
    return cutLogs(k, n, ans);
}

// Approach 3: Botoom Up DP
// Time Complexity: O(N * N * K)
// Space Complexity: O(N*K)

int cutLogs(int k, int n) {
    int dp[k+1][n+1];

    for (int i=0; i<=k; i++) { // loop for axes number
        for (int j=0; j<=n; j++) { // loop for log stand number
            dp[i][j] = j; // initialize with current log stand number which can be maximum moves
        }
    }

    for (int i=2; i<=k; i++) { 
        // start from axe = 2, because if there is only 1 axe we can cut in n number of moves only
        for (int j=2; j<=n; j++) {
            // start from n = 2, because if there is 1 capacity of log stand, it can be only one way
            for (int t = 1; t <= j; t++) { // loop for checking every combination by taking one by one
                int notPossible = dp[i-1][t-1];
                int possible = dp[i][j - t];

                int curr = max(notPossible, possible);

                dp[i][j] = min(dp[i][j], curr);
            }

            dp[i][j]++; // add one to include one move which used to check axe
        }
    }

    return dp[k][n];
}

// Approach 4: Top Down dp (optimzed with binary search)

// Time Complexity: O(N * Log N * K)
// Space Complexity: O(N*K)

int cutLogsHelper(int k, int n, vector<vector<int>> &dp) {
    // base condition
    if (k <= 0 || n <= 0) {
        return 0;
    }

    if (k == 1) {
        return n;
    }

    if (n == 1){
        return 1;
    }

    if(dp[k][n] != -1) {
        return dp[k][n];
    }

    int ans = 1e6, start = 1, end = n;

    while(start <= end) {
        int mid = start + (end - start)/2;

        if(dp[k - 1][mid - 1] == -1) {
            dp[k - 1][mid - 1] = cutLogsHelper(k - 1, mid - 1, dp);
        }

        int BREAK = dp[k-1][mid-1];

        if(dp[k][n - mid]==-1) {
            dp[k][n - mid] = cutLogsHelper(k, n - mid, dp);
        }

        int SURVIVE = dp[k][n - mid];
        ans = min (ans, 1 + max(BREAK,SURVIVE));

        if(BREAK < SURVIVE) { // if axe broken moves is less than survival means we can take more logs
            start = mid + 1;
        }
        else {
            end = mid - 1;
        }
    }
    return dp[k][n] = ans;
}

int cutLogs(int k, int n) {
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, -1));
    return cutLogsHelper(k, n, dp);
}