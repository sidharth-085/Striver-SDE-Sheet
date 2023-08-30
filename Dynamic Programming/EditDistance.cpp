#include <iostream>
#include <string>
using namespace std;

int editDistanceBF1(string str1, string str2) { // BRUTE FORCE APPROACH 1
    int m = str1.size();
    int n = str2.size();

    if (m == 0) {
        return n; // if str1 is empty, total operations are size of str2 by inserting 
                  // every character of str2 in str1.
    }

    if (n == 0) {
        return m; // if str2 is empty, total operations are size of str1 by inserting
    }             // every character of str1 in str2.

    // if (m == 0 || n == 0) {
    //   return max(m, n);
    // }

    if (str1[0] == str2[0]) { 
        // if str1[0] == str2[0], means no need to insert, replace or delete. Only need 
        // to do operations on remaining part of string, so call recursion for remaining
        // string. 
        return editDistanceBF1(str1.substr(1), str2.substr(1));
    }

    // Insert when first characters are not matching.
    // Firstly, try to perform insert operation, insert first char of str1 to str2. 
    int insertOperation = editDistanceBF1(str1.substr(1), str2) + 1;

    // Replace when first characters are not matching.
    // Secondly, try to replace first character of str2 with str1.
    int replaceOperation = editDistanceBF1(str1.substr(1), str2.substr(1)) + 1;

    // Delete when first characters are not matching.
    // Thirdly, try to delete first char from str2.
    int deleteOperation = editDistanceBF1(str1, str2.substr(1)) + 1;

    int minOperations = min(insertOperation, min(replaceOperation, deleteOperation));
    // from all operations, minimum number of operations is the answer.
    return minOperations;
}

int editDistanceUsingMemoHelper(string str1, string str2, vector<vector<int>> &ans) { // MEMOIZATION APPROACH 1
    int m = str1.size();
    int n = str2.size();

    if (m == 0) {
        return n; // if str1 is empty, total operations are size of str2 by inserting 
                  // every character of str2 in str1.
    }

    if (n == 0) {
        return m; // if str2 is empty, total operations are size of str1 by inserting
    }             // every character of str1 in str2.

    // if (m == 0 || n == 0) {
    //   return max(m, n);
    // }

    if (ans[m][n] != -1) {
        return ans[m][n];
    }

    if (str1[0] == str2[0]) { 
        // if str1[0] == str2[0], means no need to insert, replace or delete. Only need 
        // to do operations on remaining part of string, so call recursion for remaining
        // string. 
        return editDistanceUsingMemoHelper(str1.substr(1), str2.substr(1), ans);
    }

    // Insert when first characters are not matching.
    // Firstly, try to perform insert operation, insert first char of str1 to str2. 
    int insertOperation = editDistanceUsingMemoHelper(str1.substr(1), str2, ans) + 1;

    // Replace when first characters are not matching.
    // Secondly, try to replace first character of str2 with str1.
    int replaceOperation = editDistanceUsingMemoHelper(str1.substr(1), str2.substr(1), ans) + 1;

    // Delete when first characters are not matching.
    // Thirdly, try to delete first char from str2.
    int deleteOperation = editDistanceUsingMemoHelper(str1, str2.substr(1), ans) + 1;

    int minOperations = min(insertOperation, min(replaceOperation, deleteOperation));
    // from all operations, minimum number of operations is the answer.
    ans[m][n] = minOperations;
    return minOperations;
}

int editDistanceUsingMemo(string str1, string str2) {
    int m = str1.size();
    int n = str2.size();
    vector<vector<int>> ans(m+1, vector<int>(n+1, -1));
    return editDistanceUsingMemoHelper(str1, str2, ans);
}

int editDistanceBF2Helper(string str1, string str2, int m, int n) { // BRUTE FORCE APPROACH 2
    if (m == 0) {
        return n; // if str1 is empty, total operations are size of str2 by inserting
                  // every character of str2 in str1.
    }

    if (n == 0) {
        return m; // if str2 is empty, total operations are size of str1 by inserting
                  // every character of str1 in str2.
    }

    // if (m == 0 || n == 0) {
    //   return max(m, n);
    // }

    if (str1[m - 1] == str2[n - 1]) {
        // if last characters are the same, no need to insert, replace, or delete.
        // Only need to operate on the remaining substrings.
        int result = editDistanceBF2Helper(str1, str2, m - 1, n - 1);
        return result;
    }

    // Insert when last characters are not matching.
    // Firstly, try to perform insert operation, insert first char of str1 to front of str2.
    int insertOperation = editDistanceBF2Helper(str1, str2, m-1, n) + 1;

    // Replace when last characters are not matching.
    // Secondly, try to replace first character of str2 with str1.
    int replaceOperation = editDistanceBF2Helper(str1, str2, m-1, n - 1) + 1;

    // Delete when last characters are not matching.
    // Thirdly, try to delete first char from str2.
    int deleteOperation = editDistanceBF2Helper(str1, str2, m, n-1) + 1;

    int minOperations = min(insertOperation, min(replaceOperation, deleteOperation));

    return minOperations;
}

int editDistanceBF2(string str1, string str2) { // BRUTE FORCE APPROACH 2
    int m = str1.size();
    int n = str2.size();
    return editDistanceBF2Helper(str1, str2, m, n);
}

int editDistanceUsingMemoizationHelper(string str1, string str2, vector<vector<int>>& ans, int m, int n) {
    if (m == 0) {
        return n; // if str1 is empty, total operations are size of str2 by inserting
                  // every character of str2 in str1.
    }

    if (n == 0) {
        return m; // if str2 is empty, total operations are size of str1 by inserting
                  // every character of str1 in str2.
    }

    // if (m == 0 || n == 0) {
    //   return max(m, n);
    // }

    if (ans[m][n] != -1) {
        return ans[m][n];
    }

    if (str1[m - 1] == str2[n - 1]) {
        // if last characters are the same, no need to insert, replace, or delete.
        // Only need to operate on the remaining substrings.
        int result = editDistanceUsingMemoizationHelper(str1, str2, ans, m - 1, n - 1);
        ans[m][n] = result;
        return result;
    }

    // Insert when last characters are not matching.
    // Firstly, try to perform insert operation, insert first char of str1 to front of str2.
    int insertOperation = editDistanceUsingMemoizationHelper(str1, str2, ans, m-1, n) + 1;

    // Replace when last characters are not matching.
    // Secondly, try to replace first character of str2 with str1.
    int replaceOperation = editDistanceUsingMemoizationHelper(str1, str2, ans, m - 1, n - 1) + 1;

    // Delete when last characters are not matching.
    // Thirdly, try to delete first char from str2.
    int deleteOperation = editDistanceUsingMemoizationHelper(str1, str2, ans, m, n-1) + 1;

    int minOperations = min(insertOperation, min(replaceOperation, deleteOperation));
    // from all operations, minimum number of operations is the answer.
    ans[m][n] = minOperations;
    // store the minimum operations according to the size of str1 & str2.
    return minOperations;
}

int editDistanceUsingMemoization(string str1, string str2) { // MEMOIZATION APPROACH 2
    int m = str1.size();
    int n = str2.size();

    vector<vector<int>> ans(m + 1, vector<int>(n + 1, -1));
    return editDistanceUsingMemoizationHelper(str1, str2, ans, m, n);
}

int editDistanceUsingDP(string str1, string str2) { // DP APPROACH
    int m = str1.size();
    int n = str2.size();

    vector<vector<int>> ans(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++) {
        ans[i][0] = i; 
        // Initialize first column with consecutive numbers from 0 to m.
        // because if size of str1 is zero, we have to do i operations if str2 size is i.
    }

    for (int j = 0; j <= n; j++) {
        ans[0][j] = j; 
        // Initialize first row with consecutive numbers from 0 to n
        // because if size of str2 is zero, we have to do j operations if str1 size is j.
    }

    for (int i=1; i<m+1; i++) {
        for (int j=1; j<n+1; j++) {
            if (str1[i-1] == str2[j-1]) {
                ans[i][j] = ans[i-1][j-1];
            }
            else {
                int insertOperation = ans[i-1][j] + 1;
                int replaceOperation = ans[i-1][j-1] + 1;
                int deleteOperation = ans[i][j-1] + 1;

                int minOperations = min(insertOperation, min(replaceOperation, deleteOperation));
                ans[i][j] = minOperations;
            }   
        }
    }
    return ans[m][n];
}