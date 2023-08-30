#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Approach 1: Find all subsets and sort at the time of base case
// Time Complexity: O(N * Log N * 2^N)
// Space Complexity: O(N * 2^N)

// generate all subsets and sort at the time of base case
void subsets(vector<int> &arr, int si, int n, vector<int> &subset, vector<vector<int>> &ans) {
    if (si == n) {
        sort(arr.begin(), arr.end()); // sort before insertion
        ans.push_back(subset);
        return;
    }

    subset.push_back(arr[si]);
    subsets(arr, si+1, n, subset, ans); // include the element and call recursion
 
    subset.pop_back(); // backtrack and remove the element added previously
    subsets(arr, si+1, n, subset, ans); 
    // now dont include current element and call recursion
}

vector<vector<int>> pwset(vector<int> &arr) {
    vector<vector<int>> ans;

    vector<int> subset;

    subsets(arr, 0, arr.size(), subset, ans); // we got the subsets in ans array

    return ans;
}

// Approach 2: Iterative with Bitmasking 
// Time Complexity: O(N * 2^N)
// Space Complexity:

vector<vector<int>> pwset(vector<int> &arr) {
    int n = arr.size();

    sort(arr.begin(), arr.end()); // sort the array at the start

    vector<vector<int>> ans;

    for (int i=0; i < (1 << n); i++) {
        vector<int> subset;
        for (int j=0; j<n; j++) {
            if ((1 << j) & i) {
                subset.push_back(arr[j]);
            }
        }

        ans.push_back(subset);
    }

    return ans;
}

// Approach 3: Sort the array first and then create subsets
// Time Complexity: O(2^N)
// Space Complexity: O(N * 2^N)

// generate all subsets
void subsets(vector<int> &arr, int si, int n, vector<int> &subset, vector<vector<int>> &ans) {
    if (si == n) {
        ans.push_back(subset);
        return;
    }

    subset.push_back(arr[si]);
    subsets(arr, si+1, n, subset, ans); // include the element and call recursion
 
    subset.pop_back(); // backtrack and remove the element added previously
    subsets(arr, si+1, n, subset, ans); 
    // now dont include current element and call recursion
}

vector<vector<int>> pwset(vector<int> &arr) {
    sort(arr.begin(), arr.end()); // sort the array at the start

    vector<vector<int>> ans;

    vector<int> subset;

    subsets(arr, 0, arr.size(), subset, ans); // we got the subsets in ans array

    return ans;
}

// Approach 3: Iterative with Bitmasking 
// Time Complexity: O(N * 2^N)
// Space Complexity:

vector<vector<int>> pwset(vector<int> &arr) {
    int n = arr.size();

    sort(arr.begin(), arr.end()); // sort the array at the start

    vector<vector<int>> ans;

    for (int i=0; i < (1 << n); i++) { // loop to run from (0 to 2^N - 1)
        vector<int> subset; // array to store current subset

        for (int j = 0; j < n; j++) {
            if ((1 << j) & i) { // if current element is present in subset or not
                subset.push_back(arr[j]);
            }
        }

        ans.push_back(subset); // finally add the subset in ans
    }

    return ans;
}