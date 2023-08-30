#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Brute Force Approach

int largestCommonSubsequences(string str1, string str2) {
    if (str1.size() == 0 || str2.size() == 0) {
        return 0;
    }
    
    if (str1[0] == str2[0]) {
        // If the first characters of both strings match, recursively find LCS of the remaining substrings
        int ans = largestCommonSubsequences(str1.substr(1), str2.substr(1));
        return ans + 1; // Add 1 to the LCS length for the matching characters
    }

    // Find LCS by considering two options:
    // 1. Exclude the first character of str1 and continue with str2
    // 2. Exclude the first character of str2 and continue with str1
    // 3. Exclude both first characters and continue with the remaining substrings

    int option1 = largestCommonSubsequences(str1.substr(1), str2);
    int option2 = largestCommonSubsequences(str1, str2.substr(1));
    int option3 = largestCommonSubsequences(str1.substr(1), str2.substr(1));

    // Return the maximum LCS length among the two options
    int maxOption = max(option1, max(option1, option2));
    return maxOption;
}

// Memoization Approach 1
int lcsUsingMemoizationHelper1(string str1, string str2, unordered_map<string,int> &ans) {
    if (str1.size() == 0 || str2.size() == 0) {
        return 0;
    }
    
    if (ans.find(str1 + str2) != ans.end()) {
         return ans[str1 + str2]; // Return the precalculated LCS if it exists in the memoization map
    }

    if (str1[0] == str2[0]) {
        // If the first characters of both strings match, recursively find LCS of the remaining substrings
        int result = lcsUsingMemoizationHelper1(str1.substr(1), str2.substr(1), ans);
        ans[str1 + str2] = result + 1; // Store the calculated LCS in the memoization map
        return result + 1; // Add 1 to the LCS length for the matching characters
    }

    // Find LCS by considering two options:
    // 1. Exclude the first character of str1 and continue with str2
    // 2. Exclude the first character of str2 and continue with str1
    // 3. Exclude both first characters and continue with the remaining substrings

    int option1 = lcsUsingMemoizationHelper1(str1.substr(1), str2, ans);
    int option2 = lcsUsingMemoizationHelper1(str1, str2.substr(1), ans);
    int option3 = lcsUsingMemoizationHelper1(str1.substr(1), str2.substr(1), ans);

    // Return the maximum LCS length among the two options
    int maxOption = max(option1, max(option1, option2));
    ans[str1 + str2] = maxOption; // Store the calculated LCS in the memoization map
    return maxOption;
}

int lcsUsingMemoization1(string str1, string str2) {
    unordered_map<string, int> ans; // Map to store precalculated LCS for subproblems
    return lcsUsingMemoizationHelper1(str1, str2, ans);
}

// Memoization Approach 2
int lcsUsingMemoizationHelper2(string str1, string str2, vector<vector<int>> &ans) {
    int m = str1.size();
    int n = str2.size();

    if (m == 0 || n == 0) {
        return 0;
    }

    if (ans[m][n] != -1) {
        return ans[m][n]; // Return the precalculated LCS if it exists in the memoization table
    }

    if (str1[0] == str2[0]) {
        // If the first characters of both strings match, recursively find LCS of the remaining substrings
        int result = lcsUsingMemoizationHelper2(str1.substr(1), str2.substr(1), ans);
        ans[m][n] = result + 1; // Store the calculated LCS in the memoization table
        return result + 1; // Add 1 to the LCS length for the matching characters
    }

    // Find LCS by considering three options:
    // 1. Exclude the first character of str1 and continue with str2
    // 2. Exclude the first character of str2 and continue with str1
    // 3. Exclude both first characters and continue with the remaining substrings
    int option1 = lcsUsingMemoizationHelper2(str1.substr(1), str2, ans);
    int option2 = lcsUsingMemoizationHelper2(str1, str2.substr(1), ans);
    int option3 = lcsUsingMemoizationHelper2(str1.substr(1), str2.substr(1), ans);

    // Return the maximum LCS length among the three options
    int maxOption = max(option1, max(option2, option3));
    ans[m][n] = maxOption; // Store the calculated LCS in the memoization table
    return maxOption;
}

int lcsUsingMemoization2(string str1, string str2) {
    int m = str1.size();
    int n = str2.size();
    vector<vector<int>> ans(m + 1, vector<int>(n + 1, -1)); // Table to store precalculated LCS for subproblems
    return lcsUsingMemoizationHelper2(str1, str2, ans);
}

// Dp approach
int lcsUsingDP(string str1, string str2) {
    int m = str1.size();
    int n = str2.size();

    // Create a 2D DP table with (m+1) rows and (n+1) columns
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Fill in the DP table
    dp[0][0] = 0; // Base case when str1 or str2 size is 0.

    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                // If the characters at the current positions are the same, add 1 to the LCS length
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                // If the characters at the current positions are different, choose the maximum LCS length
                // by considering the LCS of the substrings formed by excluding either str1[i-1] or str2[j-1]
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Return the LCS length
    return dp[m][n];
}

int main() {
    cout << largestCommonSubsequences("xyz", "zxy") << endl;
    cout << lcsUsingMemoization1("xyz", "zxy") << endl;
    cout << lcsUsingMemoization2("xyz", "zxy") << endl;
    cout << lcsUsingDP("xyz", "zxy") << endl;
}