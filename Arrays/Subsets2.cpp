#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

// Approach 1: Using Recursion with Set to avoid duplicates
// Time Complexity: O(2^N * Log N)
// Space Complexity: O(2^N)

void helper(vector<int> &arr, int si, vector<int> &temp, vector<vector<int>> &ans, set<vector<int>> &st, int n) {
    // Base case: When the start index reaches the size of the array

    if (si == n) {
        // If the current subset is not already in the set, add it to the set and 
        // the answer

        if (st.find(temp) == st.end()) {
            ans.push_back(temp);
            st.insert(temp);
        }
        return; 
    }

    // Include the current element in the subset
    temp.push_back(arr[si]);
    helper(arr, si + 1, temp, ans, st, n); // Recursive call for the next element

    // Exclude the current element from the subset
    temp.pop_back();
    helper(arr, si + 1, temp, ans, st, n); 
    // Recursive call without the current element
}

vector<vector<int>> uniqueSubsets(int n, vector<int> &arr) {
    sort(arr.begin(), arr.end()); // Sort the input array

    vector<vector<int>> ans;
    vector<int> temp; // Temporary vector to store the current subset

    set<vector<int>> st; // Set to keep track of unique subsets

    // Start the recursive generation of unique subsets
    helper(arr, 0, temp, ans, st, n);

    sort(ans.begin(), ans.end()); // Sort the answer to match the required order

    return ans;
}

// Approach 2: Bitmasking Iteratively with Set to avoid Duplicates
// Time Complexity: O(2^N * N)
// Space Complexity: O(2^N)

vector<vector<int>> uniqueSubsets(int n, vector<int> &arr) {
    sort(arr.begin(), arr.end()); // Sort the input array

    vector<vector<int>> ans; 
    set<vector<int>> st; // Set to keep track of unique subsets

    // Iterate through all possible binary numbers from 0 to 2^n - 1
    for (int i = 0; i < (1 << n); i++) {
        vector<int> temp; 
        // Temporary vector to store the current subset

        // Extract elements from the input array based on the set bits in 'i'
        for (int j = 0; j < n; j++) {
            // Check if jth bit is set in 'i'

            if ((1 << j) & i) { 
                temp.push_back(arr[j]); 
                // Include the corresponding element in the subset
            }
        }

        // If the current subset is not already in the set, add it to the answer
        if (st.find(temp) == st.end()) {
            ans.push_back(temp);
        }

        st.insert(temp); // Add the current subset to the set of unique subsets
    }

    sort(ans.begin(), ans.end()); // Sort the answer to match the required order

    return ans; // Return the vector of unique subsets
}