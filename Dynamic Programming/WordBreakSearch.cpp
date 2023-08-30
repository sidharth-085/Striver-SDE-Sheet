#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

// This problem is saying that we have to make target string from words present in words 
// array

// We can also say that we have to check that if we break target string, every word 
// should present in dictionary

// We will follow second approach to solve this question

// Approach 1: Recursion
// Time Complexity: O(2^N)
// Space Complexity: O(1)

bool wordBreak(vector<string> &words, int n, string target) {
    int size = target.size();

    // step 1: check the base case if target size is 0, means we searched complete target
    // return true

    if (size == 0) {
        return true;
    }

    // step 2: check for every possible combination, break the string into two halves
    // from 0 to i && i to size - i

    for (int len = 1; len <= size; len++) { // run loop from 1 to size
        bool flag = false;

        string substr = target.substr(0, len); // first half of substring from 0 to len
        for (int i = 0; i < n; i++) {
            if (substr == words[i]) { // check if current substring found in given words dictionary
                flag = true; // mark flag true and break for checking for remaining string
                break;
            }
        }

        if (flag == true && wordBreak(words, n, target.substr(len, size - len)) == true) {
            // if the substr found in words array && remaining string also present in words dictionary
            // then return true
            return true;
        }
    }

    return false; // if we dont get any solution till end, return false.
}

// Approach 2: Using Hashmap or hashset
// Time Complexity: O(2^N)
// Space Complexity: O(N)

bool wordBreak(vector <string> &arr, int n, string target, unordered_set<string> &map) {
    int size = target.size();

    if (target.size() == 0) {
        return true;
    }

    for (int len = 1; len <= size; len++) {
        string substr = target.substr(0, len);
        if (map.find(substr) != map.end() && wordBreak(arr, n, target.substr(len, size-len), map) == true) {
            return true;
        }
    }

    return false;
}

bool wordBreak(vector <string> &arr, int n, string target) {
    unordered_set<string> map;

    for (int i=0; i<n; i++) {
        map.insert(arr[i]);
    }    

    return wordBreak(arr, n, target, map);
}

// Approach 3: Using Memoization (Top-down DP)

// It improves time complexity O(N*N) (removing the comparing loop & applying memoization)with 
// using O(N) space.

// It can be little more optimized by taking vector of lengths of strings instead of map
// map will do hashing internally, which makes time complexity little bad
// so we can make a vector of size = length of target && pass as argument to solve.

bool wordBreak(vector <string> &arr, int n, string target, unordered_map<string, int> &ans, unordered_set<string> &map) {
    int size = target.size();
    if (target.size() == 0) { // start == target.size()
        return true;
    }

    if (ans[target] != 0) { // ans[start] != -1
        return ans[target] == 1; // 1 represents true, -1 represents false
    }

    for (int len = 1; len <= size; len++) { // len >> (start+1) -> size
        string substr = target.substr(0, len);

        string rem = target.substr(len, size-len);

        if (map.find(substr) != map.end() && wordBreak(arr, n, rem, ans, map) == true) {
            return true;
        }
    }

    ans[target] = -1;
    return false;
}

bool wordBreak(vector <string> &arr, int n, string target) {
    unordered_set<string> map; // hashmap to avoid checking loop 

    for (int i=0; i<n; i++) {
        map.insert(arr[i]);
    }  

    unordered_map<string, int> ans; // memoization map
    return wordBreak(arr, n, target, ans, map);
}

// Approach 4: Bottom Up Dp
// lets apply vector of target.size() discussed above

// Time Complexity: O(N*N)
// Space Complexity: O(N)

bool wordBreak(vector <string> &arr, int n, string target) {
    unordered_set<string> map;

    for (int i=0; i<n; i++) {
        map.insert(arr[i]);
    }

    vector<bool> dp(target.size() + 1, false);

    // base case: when target length is zero
    dp[0] = true;

    for (int i=1; i <= target.size(); i++) {
        for (int j = i-1; j >= 0; j--) { // here j represents the start which discussed above
            // in recursion, we start with 0 here we end with 0 (bottom up)

            string substr = target.substr(j, i-j);
            if (map.find(substr) != map.end() && dp[j] == true) {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[target.size()];
}