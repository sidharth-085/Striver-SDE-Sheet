#include <vector>
using namespace std;

// Basic Recursive Solution: Include - exclude element pattern
// Time Complexity: O(2^N)

bool subsetSumToK(int n, int sum, vector<int> &arr) {
    if (sum == 0) { // if sum is zero, means we find the subset return true
        return true;
    }

    if (n == 0) { // when sum is not zero but n = 0 means array ends, return false
        return false;
    }

    // include element & check is subset present in remaining array

    bool option1 = subsetSumToK(n-1, sum - arr[n-1], arr); 
    if (option1 == true) {
        return true;
    }

    // now if included element dont get the subset, try excluding the element.

    return subsetSumToK(n-1, sum, arr);
}

// Memoization Approach:

// Time Complexity: O(N*Sum)
// Space Complexity: O(N*Sum)

bool subsetSumToK(int n, int sum, vector<int> &arr, vector<vector<int>> &ans) {
    if (sum == 0) {
        return true;
    }

    if (n == 0) {
        return false;
    }

    if (ans[n][sum] != -1) { // two parameters are changing size of arr && sum 
        return ans[n][sum];
    }

    bool include = false;
    if (arr[n-1] <= sum) {
        include = subsetSumToK(n-1, sum - arr[n-1], arr, ans);
    }

    if (include == true) {
        return true;
    }

    ans[n][sum] = subsetSumToK(n-1, sum, arr, ans);

    return ans[n][sum];
}

bool subsetSumToK(int n, int sum, vector<int> &arr) {
    vector<vector<int>> ans(n+1, vector<int>(sum+1, -1)); // memoization array
    return subsetSumToK(n, sum, arr, ans);
}

// Dp solution: Iterative Dp 

// Time Complexity: O(N*Sum)
// Space Complexity: O(N*Sum)

bool subsetSumToK(int n, int sum, vector<int> &arr) {
    vector<vector<bool>> ans(n+1, vector<bool>(sum+1));

    for (int i=0; i<=n; i++) { // if sum = 0, means we found the subset
        ans[i][0] = true;
    }

    for (int i=0; i<=sum; i++) { // if array is completed, n = 0, subset not found
        ans[0][i] = false;
    }

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=sum; j++) {
            if (arr[i - 1] <= j) {
                bool include = ans[i - 1][j - arr[i - 1]]; // check by including the current element.
                if (include == true) { // if subset found by including, add true to dp
                    ans[i][j] = true;
                }
                else { // else add to dp by excluding the current element
                    ans[i][j] = ans[i - 1][j];
                }
            } 
            else { // if current element is bigger, exclude the element and check for remaining
                ans[i][j] = ans[i - 1][j];
            }
        }
    }
    return ans[n][sum];
}
