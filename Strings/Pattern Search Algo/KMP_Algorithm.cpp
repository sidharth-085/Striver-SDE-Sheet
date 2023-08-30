#include <iostream>
#include <string>
using namespace std;

// In this question, we have given two strings S and P, we need to search pattern P in 
// string S

// Brute Force Approach: Two Pointer Approach

bool findPattern(string pattern, string str) {
    if (pattern.size() > str.size()) { // if string S is smaller than P, return false.
        return false;
    }

    int i = 0; // pointer for pattern
    int j = 0; // pointer for string

    int lastMatchIndex = -1; // keeps track of the last successful match index

    while (i < pattern.size() && j < str.size()) {
        if (pattern[i] == str[j]) {
            if (i == 0) {
                lastMatchIndex = j; 
                // set lastMatchIndex to the current index if it's the start of a new match
            }
            i++;
            j++;
        } 
        else {
            if (lastMatchIndex != -1) {
                j = lastMatchIndex + 1; 
                // reset j to the next index after the last successful match
            } 
            else {
                j++; // if no successful match yet, simply move to the next character in the string
            }

            i = 0; // reset the pattern pointer to the beginning
            lastMatchIndex = -1; // reset the lastMatchIndex
        }
    }

    if (i == pattern.size()) {
        return true;
    }
    return false;
}

// Now the Optimal way is KMP Algorithm

// KMP algorithm requires LPS array to do functioning in Time Complexity: O(N+M).

void computeLPSArray(string pattern, int size, int* lps) {
    int len = 0; // make the variable len which stores the lps of previous.
    lps[0] = 0; // first prefix is always 0.  

    int i = 1; // start from index 1

    while (i < size) {
        if (pattern[i] == pattern[len]) { // if we get match, lps[i] will be len + 1.
            len++;
            lps[i] = len;
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

bool findPattern(string pattern, string str) {
    int n = pattern.size();
    int m = str.size();

    int *lps = new int[n];
    computeLPSArray(pattern, n, lps); // now we get the lps array for pattern

    int i = 0; // pointer for pattern
    int j = 0; // pointer for string

    while (j < m) { // iterate over complete string str
        if (pattern[i] == str[j]) {
            i++;
            j++;
        }

        if (i == n) {
        /*
            If we want to print from which index we found the pattern, we have to add two 
            lines below and avoid return statement (choose function type void).
            
            cout << "found pattern in string str at index : " << j - i << endl;
            j = lps[j-1];
            
        */
            return true;
            // we find the pattern, return true
            // pattern will start from (i - j)th index in string str
        }

        else if (j < m && pattern[i] != str[j]) {
            if (i == 0) {
                j++; 
                // if i and j are not matching and initially we are at i = 0 in pattern 
                // just moves next char in string str    
            }
            else {
                i = lps[i-1];
                // but we are standing at non zero index and characters are not matching
                // update i to prev lps.
            }
        }
    }
    return false;
}