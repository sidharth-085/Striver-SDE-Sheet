#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Naive Approach: O(N^3) Time Complexity

// Function to check if a string is a palindrome
bool checkPalindrome(string str) {
    int start = 0;
    int end = str.size() - 1;
    while (start < end) {
        if (str[start] != str[end]) {
            return false;
        }
        start++;
        end--;
    }
    return true;
}

// Function to find the longest palindrome substring using a naive approach
string longestPalinSubstring(string str) {
    int size = str.size();
    string output;

    for (int i=0; i<size; i++) {
        for (int len = 1; len <= size - i; len++) {
            // Extract substrings starting from index i with different lengths
            string temp = str.substr(i, len);
            if (checkPalindrome(temp) && temp.size() > output.size()) {
                // If the substring is a palindrome and its length is greater than the current longest palindrome,
                // update the output string
                output = temp;
            }
        }
    }
    return output;
}

// Dynamic Programming Approach
// Time Complexity: O(N^2)

// Function to find the longest palindrome substring using dynamic programming
string longestPalinSubstring(string str) {
    int n = str.size();

    if (n <= 1) {
        return str;
    }

    int start = 0;
    int maxLength = 1;

    // Create a 2D dynamic programming array to store the palindrome information
    vector<vector<bool>> dp(n, vector<bool>(n, false));

    // Mark single characters as palindromes
    for (int i=0; i<n; i++) {
        dp[i][i] = true;
    }

    // Check for substrings of length 2
    for (int i = 0; i < n - 1; i++) {
        if (str[i] == str[i+1]) {
            dp[i][i+1] = true;

            if (maxLength < 2) {
                maxLength = 2;
                start = i;
            }
        }
    }

    // Check for substrings of length greater than 2
    for (int len = 3; len <= n; len++) {
        for (int i=0; i <= n-len; i++) {
            int j = i + len - 1;
            // Check if the substring from i+1 to j-1 is a palindrome and str[i] is equal to str[j]
            if (dp[i+1][j-1] == true && str[i] == str[j]) {
                dp[i][j] = true;

                if (maxLength < len) {
                    maxLength = len;
                    start = i;
                }
            }
        }
    }

    return str.substr(start, maxLength);
}

// Approach: Expand from Centre method
// Time Complexity: O(N^2)

// Function to expand from the center of a string and find the length of the palindrome
int expandFromCentre(string str, int left, int right) {
    int n = str.size();
    int start = left;
    int end = right;

    while (start >= 0 && end < n && str[start] == str[end]) {
        start--;
        end++;
    }

    return end - start - 1;
}

// Function to find the longest palindrome substring using the expand from center method
string longestPalinSubstring(string str) {
    int n = str.size();

    int start = 0;
    int end = 0;

    if (n <= 1) {
        return str;
    }

    for (int i=0; i<n; i++) {
        int len1 = expandFromCentre(str, i, i);       // Odd-length palindromes
        int len2 = expandFromCentre(str, i, i+1);     // Even-length palindromes

        int len = max(len1, len2);
        int currLen = end - start + 1;

        if (currLen < len) {
            start = i - (len - 1)/2;
            end = i + (len)/2;
        }
    }
    return str.substr(start, end - start + 1);
}

int main() {
    string str = "babad";
    cout << longestPalinSubstring(str) << endl;  // Output: "bab" or "aba"

    return 0;
}