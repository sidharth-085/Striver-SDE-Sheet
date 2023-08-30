#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
using namespace std;

// Approach 1: Brute Force Method
// Time Complexity: O(N^3)
// Space Complexity: O(N)

int maxLengthOfSubstringWithoutRepeatingCharacters(string input, int n) {
    int ans = 0;

    // step 1: generate all substrings and then check for every substring

    for (int i=0; i<n; i++) {
        for (int len = 1; len <= n - i; len++) {
            // step 2: for current substring check the number of distinct characters
            // using map

            string curr = input.substr(i, len);
            unordered_map<char, int> map;

            int k = len;

            for (int j=0; j<len; j++) {
                map[curr[j]]++;
            }

            // step 3: if distinct characters equal to k, means in the current substring
            // all the characters are distinct. Compare with ans, if more update ans.
        
            if (map.size() == k) {
                ans = max(ans, k);
            }
        }
    }

    return ans;
}

int uniqueSubstrings(string input) {
    int n = input.size();

    return maxLengthOfSubstringWithoutRepeatingCharacters(input, n);
}

// Approach 2: Sliding Window approach, trying every possible window from 1 to N
// Time Complexity: O(N^2)
// Space Complexity: O(N)

int uniqueSubstrings(string input) {
    int n = input.size();

    // step 1: traverse every possible window from 1 to N.

    int ans = 0;

    for (int k=1; k<=n; k++) {
        // step 2: for the current window size k, make map to store distinct characters
        // for current window

        unordered_map<char, int> map;

        // step 3: traverse the first window and add all the inputs and if size of 
        // map becomes equal to window size means all characters are distinct so, 
        // compare with ans.

        for (int i=0; i<k; i++) {
            map[input[i]]++;
        }

        if (map.size() == k) {
            ans = max(ans, k);
        }

        // step 4: now for next window, keep a pointer to remove previous window element

        int j = 0;

        for (int i=k; i<n; i++) {
            map[input[j]]--;
            // first remove the previous window element and if frequency becomes 0
            // erase it from map

            if (map[input[j]] == 0) {
                map.erase(input[j]);
            }

            // now add current window element to the map and now again check for 
            // map size, if equal to k means all characters are distinct so compare
            // with ans

            map[input[i]]++;

            if (map.size() == k) {
                ans = max(ans, k);
            }

            j++;
            // finally move the previous window pointer ahead
        }
    }

    return ans;
}

// Approach 3: Optimal Method
// Time Complexity: O(N)
// Space Complexity: O(N)
 
int uniqueSubstrings(string input) {
    int n = input.size();
    int maxLen = 0;

    unordered_set<char> set;
    // creating a set to store the characters which are non repeating

    int i = 0; int j = 0;
    // two pointers for representing the window start both pointers from 0
    // i is the pointer which moves forward for every iteration and window
    // j is the pointer represents in the starting of the window

    // run the loop till i and j are less than n

    while (i < n && j < n) {
        // first check is current character is already present in the set or not
        // if not present, it means we found the substring with non repeating chars
        // update the maxLen if currLen is bigger.

        if (set.find(input[i]) == set.end()) {
            int currLen = i - j + 1;
            maxLen = max(maxLen, currLen);

            // now if ith character doesn't exists in set, insert it to keep the 
            // current substring with distinct characters and also moves the j pointer 
            // ahead which moves to next character

            set.insert(input[i]);
            i++;
        }
        else {
            // now if current character is already present in the set, it means the 
            // current substring holds duplicate values, so remove the character from
            // set and move the start pointer of current substring ahead.

            set.erase(input[j]);
            j++;
        }
    }

    return maxLen;
}