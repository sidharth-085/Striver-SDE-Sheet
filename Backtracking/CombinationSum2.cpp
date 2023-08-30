#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

// This approach is good, but uses so much memory in diff data structures & time complexity
// Time Complexity: O(2^N * N * Log*n)

void helper(vector<int> &arr, vector<vector<int>> &ans, vector<int> &subArr, int target, int n, int si) {
	if (si == n) {
		if (target == 0) {
			ans.push_back(subArr);
		}
		return;
	}

	helper(arr, ans, subArr, target, n, si+1);

	subArr.push_back(arr[si]); // add the element to the subarr (include the arr[si] element)

	helper(arr, ans, subArr, target - arr[si], n, si+1); // call recursion for remaining part.

	subArr.pop_back();
    // backtrack and remove the number from subarr and str for next elements to be taken
}

vector<vector<int>> combinationSum2(vector<int> &arr, int n, int target) {
    sort(arr.begin(), arr.end()); // first sort the array to get the sorted order subsets.

	vector<vector<int>> ans; // make the final ans grid in which we store answers

	vector<int> subArr; // this stores particular subarr and push in ans grid.

	helper(arr, ans, subArr, target, n, 0);
	sort(ans.begin(), ans.end()); // sort the final grid to get lexicographical order of subsets.

	ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
    // this function only keeps unique elements, and removes use of map
    return ans;
}

// Brute force approach with Bitmasking (same as Subset to sum K)
// Time Complexity: O(N * 2^N * Log (2^N)) = O(N^2 * 2^N)

vector<vector<int>> combinationSum2(vector<int> &arr, int n, int target) {
    // Sort the given array
    sort(arr.begin(), arr.end());

    vector<vector<int>> result;
    // Find and check all 2^n combinations.
    for(int i = 0; i < (1 << n); i++) {
        vector<int> comb;
        int sum = 0;
        for(int j = 0; j < n; j++)  {
            if(i & (1 << j)) {
                // Append jth element of array if jth bit of 'i' is set
                comb.push_back(arr[j]);
                sum += arr[j];
            }
        }
        // Add 'comb' in vector result.
        if(sum == target) {
            result.push_back(comb);
        }
    }
        
    // arrange all combinations in lexicographical order in 'result'.
    sort(result.begin(), result.end());

    // Remove duplicates from vector 'result'.
    result.resize(unique(result.begin(), result.end()) - result.begin());
    
    return result;
}

// Using Backtracking Efficiently
// Time Complexity: O(2^N)

void helper(vector<int> &arr, int n, int target, vector<vector<int>> &ans, vector<int> &subArr, int si) {
	if (target == 0) {
		ans.push_back(subArr);
		return;
	}

	for (int i=si; i<n; i++) {
		if (arr[i] > target) { // check if the current element is bigger than target then, backtrack
			break;
		}
		if (i > si && arr[i] == arr[i-1]) {
			continue;
		}
		subArr.push_back(arr[i]); // add the element in subarr and call recursion to explore remaining array

		helper(arr, n, target - arr[i], ans, subArr, i+1);

		subArr.pop_back(); // if solution not gets answer, backtrack & remove the last element
	}
}

vector<vector<int>> combinationSum2(vector<int> &arr, int n, int target){
	sort(arr.begin(), arr.end());

	vector<vector<int>> ans;
	vector<int> subArr;

	helper(arr, n, target, ans, subArr, 0);
	return ans;
}