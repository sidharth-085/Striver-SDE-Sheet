#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Approach 1: Brute Force Approach
// Time Complexity: O(N^2)
// Space Complexity: O(1)

/*  Method is simple, just keep two pointers when start and end chars are not equal, 
    decrease the end index and increase count and if palindrome is found, break.
  
    int minCharsforPalindrome(string str) {
    int n = str.size();

    int start = 0;
    int end = n-1;

    int count = 0;

    while (start <= end) {
        if (checkPalindrome(str, start, end)) {
            break;
        }
        else {
            count++;
            end--;
        }
    }

    return count;
}

*/

bool checkPalindrome(string str, int start, int end) { // string is palindrome or not
    while (start <= end) {
        if (str[start] != str[end]) {
            return false;
        }
        start++;
        end--;
    }

    return true;
}

int minCharsforPalindrome(string str) {
    int n = str.size();

    int lastPalindromeLoc = 0;
    // this keeps the index where the last permutation ends from 0

    for (int i=0; i<n; i++) {
        if (checkPalindrome(str, 0, i)) {
            lastPalindromeLoc = i;
        }
    }

    return n - lastPalindromeLoc - 1;

    // so from 0 to index till there last permutation exists, we need remaining 
    // characters present in string so return n - lastPalindromeLoc - 1.
}

// Approach 2: Better Brute Force Solution using Extra Space
// Time Complexity: O(N^2)
// Space Complexity: O(N^2)

int minCharsforPalindrome(string str) {
     int n = str.size();

    int lastPalindromeLoc = 0;

    vector<vector<bool>> palCheck(n, vector<bool>(n, false));
    // in this approach instead of checking everytime is string from 0 to ith index
    // is palindrome or not, we calculate it in single go.

    for (int j=0; j<n; j++) {
        for (int i=0; i<=j; i++) {
            if (str[i] == str[j] && (j-i+1 <= 2 || palCheck[i+1][j-1] == true)) {
                palCheck[i][j] = true;
            }
        }
    }

    for (int i=0; i<n; i++) {
        if (palCheck[0][i] == true) {
            lastPalindromeLoc = i;
        }
    }

    return n - lastPalindromeLoc - 1;
}

// Approach 3: Most Optimal Solution
// Time Complexity: O(N)
// Space Complexity: O(1)

int minCharsforPalindrome(string str) {
    int n = str.size();

    // step 1: keeps 2 pointers same as approach 1 (commented)

    int start = 0;
    int end = n-1;

    // step 2: make a count variable to keep count of min characters required and 
    // variable k which start from ending

    int count = 0;
    int k = n-1;

    while (start <= end) {
        // step 3: so if start and end character is palindrome just increase start
        // decrease end

        if (str[start] == str[end]) {
            start++;
            end--;
        }

        // step 4: but if start and end characters are not equal, first me move start
        // to the 0. Pull k backward and make the end as k and finally increase the 
        // count by 1.

        // basically this k acts as same as lastPalindromeLoc (same in approach 1).

        else {
            start = 0;
            k--;
            end = k;
            count++;
        }
    }

    return count;
    // return n - k - 1;
    
    // it will give same answer because we are first checking that start and end character
    // if both characters are equal, means there can be a chance that string is palindrome
    // so we move to start + 1 and end - 1. But if start + 1 to end - 1 string is not
    // a palindrome, it means k which denotes the last palindrome location, need to shift
    // back and check again from 0 to k substring and repeating the process.
}