#include <iostream>
#include <vector>
#include <string>
using namespace std;

// General Solution with Check Palindrome function to check every substr.

bool checkPalindrome(string &str) { // function to check is string palinrome
    int start = 0;
    int end = str.size() - 1;

    while (start <= end) {
        if (str[start] != str[end]) {
            return false;
        }
        start++;
        end--;
    }
    return true;
}

void partitionString(int partitionIndex, string &str, vector<string> &palSubStr, vector<vector<string>> &ans) {
    if (partitionIndex == str.size()) {
        ans.push_back(palSubStr); // when reaches to empty string, add palsubstr to ans.
        return;
    }

    for (int i=partitionIndex; i<str.size(); i++) {
        string subStr = str.substr(partitionIndex, i-partitionIndex+1);
        if (checkPalindrome(subStr) == true) {
            palSubStr.push_back(subStr); 
            // insert the substring in vector

            partitionString(i + 1, str, palSubStr, ans); 
            // call recursion for other half of partitioned string.

            palSubStr.pop_back(); 
            // backtrack and remove the current string.
        }
    }
}

vector<vector<string>> partition(string &str) {
    vector<vector<string>> ans;
    vector<string> palSubStr;
    int start = 0;

    partitionString(start, str, palSubStr, ans);
    return ans;
}

// We can avoid everytime checking is Substring palindrome by using Dynamic Programming
// but it uses O(N ^ 2) space which increases time & space complexity.

/*
    Time Complexity: O(N * ( 2 ^ N ))
    Space Complexity: O(N ^ 2)

    Where 'N' is the length of string.
*/

void partitionHelper(string &s, int start, vector<vector<string>> &ans, vector<string> &currentList, vector<vector<bool>> &dp) {

    // If start reach the end of String.
    if (start >= s.length()) {
        // Add the current generated Palindromic Partition to answer List.
        ans.push_back(currentList);
        return;
    }

    for (int k = start; k < s.length(); k++) {

        // Check if substring S[start...k] is Palindrome or not.
        if (dp[start][k]) {
            // Add the substring S[start...k].
            currentList.push_back(s.substr(start, k + 1 - start));

            // Recurence for rest of the string to get all the palindromic partitions.
            partitionHelper(s, k + 1, ans, currentList, dp);

            // Remove the substring S[start...k] from current partition.
            currentList.pop_back();

        }
    }
}

vector<vector<string>> partition(string &s)  {
    // It store all the possible palindromic partitions.
    vector<vector<string>> ans;

    // Create a boolean dp for checking substing[i..j] is palindrome or not.
    vector<vector<bool>> dp (s.length(), vector <bool> (s.length(), false));
    for (int j = 0; j < s.length(); j++) {
        for (int i = 0; i <= j; i++) {
            if (s[i] == s[j] && (j - i < 2 || dp[i + 1][j - 1])) {
                // condition for palindrome: If i & j character is same && string from
                // i+1 to j-1 is palindrome, string from i to j is also palindrome
                dp[i][j] = true;
            }
        }
    }

    vector<string> currentList;
    // Recursive function to generate all the possible palindromic partitions.
    partitionHelper(s, 0, ans, currentList, dp);

    return ans;
}