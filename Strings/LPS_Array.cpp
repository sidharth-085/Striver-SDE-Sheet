#include <iostream>
#include <vector>
using namespace std;

// LPS (Longest Proper Prefix Suffix Array) is important array for KMP algorithm for 
// pattern searching problem

// Proper Prefix is a prefix having length less than equal to length of string.

// for example: string = "ababacab"
// The LPS array will be {0, 0, 1, 2, 1, 0, 1, 2}
// check the proper prefixes and suffixes for particular length of string

// for length 5 for example, we have proper prefixes "a", "ab", "aba", "abab" & suffix
// "a", "ba", "aba", "baba", "ababa"

// only "a" and "a" matches so we have longest proper prefix suffix length 1 which stores on 
// 4th index.

// This method of LPS takes O(N^3) Time complexity

int findLPS(string str, int size) {
    for (int len = size-1; len > 0; len--) { // this decides the length of prefix
        bool flag = true;
        for (int i = 0; i < len; i++) { // loop iterates to get prefix 0 to len
            if (str[i] != str[i + size - len]) { 
                // check if characters of prefix and suffix matches or not, if not
                // mark flag false
                flag = false;
            }
        }
        if (flag == true) {
            return len;
        }
    }
    return 0;
}

vector<int> fillLPS(string str, int n) {
    vector<int> lps(n);
    for (int i=0; i<n; i++) {
        lps[i] = findLPS(str, i+1);
    }
    return lps;
}

// To optimise this, we can use pre-computed LPS
// Time Complexity : O(M) where M is length of pattern

void computeLPSArray(string pattern, int size, int* lps) {
    int len = 0; // make the variable len which stores the lps of previous.
    lps[0] = 0; // first prefix is always 0.  

    int i = 1; // start from index 1

    while (i < size) {
        if (pattern[i] == pattern[len]) { // if we get match, lps[i] will be len + 1.
            lps[i] = len + 1;
            len++;
            i++;
        }
        else { // if pattern[i] != pattern[len]
            if (len == 0) { // check is len == 0, if yes it means prev lps is 0
                lps[i] = 0;
                i++;   
            }
            else {
                len = lps[len - 1];
            }
        }
    }
}