#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Brute Force Approach (find all subsets and take the sum of it)
// Time Complexity: O(N * 2^N)
// Space Complexity: O(N)

void subsets(vector<int> &nums, vector<int> &ans, int si, int n, vector<vector<int>> &subs) {
	if (si == n) {
		subs.push_back(ans);
		return;
	}

	ans.push_back(nums[si]);
	subsets(nums, ans, si + 1, n, subs); // include the element

	ans.pop_back();
	subsets(nums, ans, si + 1, n, subs); // not include the element
}

vector<int> subsetSum(vector<int> &nums) {
	vector<int> ans;
	vector<vector<int>> subs;

	subsets(nums, ans, 0, nums.size(), subs);

	ans.erase(ans.begin(), ans.end());

	for (int i=0; i<subs.size(); i++) {
		if (subs[i].size() == 0) {
			ans.push_back(0);
		}
		else {
			int sum = 0;
			for (int j=0; j<subs[i].size(); j++) {
				sum = sum + subs[i][j];
			}

			ans.push_back(sum);
		}
	}

	sort(ans.begin(), ans.end());

	return ans;
}

// Approach 2: Optimal Approach (finding sum at the time of base case) (better)
// Time Complexity: O(N * 2^N) [O(2^N * Log 2^N)]
// Space Complexity: O(N)

// this subset function generates 2^N subsets and their sum.

void subsets(vector<int> &nums, vector<int> &temp, int si, int n, vector<int> &ans) {
	if (si == n) {
		if (temp.size() == 0) {
			ans.push_back(0);
		}
		else {
			int sum = 0;
			for (int i=0; i<temp.size(); i++) {
				sum = sum + temp[i];
			}

			ans.push_back(sum);
		}
		return;
	}

	temp.push_back(nums[si]);
	subsets(nums, temp, si + 1, n, ans); // include the element

	temp.pop_back(); // backtrack and remove the previously added element
	subsets(nums, temp, si + 1, n, ans); // not include the element
}

vector<int> subsetSum(vector<int> &nums) {
	vector<int> temp;
	vector<int> ans; // this vector contains sum of 2^N subsets

	subsets(nums, temp, 0, nums.size(), ans);

	sort(ans.begin(), ans.end()); // sorting 2^N elements take O(2^N * Log 2^N) time.

	return ans;
}

// Approach 3: Find subset sum at the time of recursion (optimal)
// Time Complexity: O(N * 2^N)
// Space Complexity: O(N)

void subsets(vector<int> &nums, int si, int n, int sum, vector<int> &ans) {
    if (si == n) {
        ans.push_back(sum);
        return;
    }

    subsets(nums, si + 1, n, sum + nums[si], ans); // include the element

    subsets(nums, si + 1, n, sum, ans); // not include the element
}

vector<int> subsetSum(vector<int> &nums) {
    vector<int> ans; // this vector contains sum of 2^N subsets

	subsets(nums, 0, nums.size(), 0, ans);

	sort(ans.begin(), ans.end()); // sorting 2^N elements take O(2^N * Log 2^N) time.

	return ans;
}

// Approach 4: Iterative and BitMasking (most optimal and mostly used method)
// Time Complexity: O(N * 2^N)
// Space Complexity: O(1)

/*
    The idea is to denote every subset as a binary representation of a positive 
    integer. For example, let the size of a given array is 3 and an integer 5, which 
    has a binary representation “101”, here “101” means we take a subset which has 
    elements 1st and 3rd(1 means include the element and 0 means not include the 
    element). LSB of  “101” represents the first element of the array and MSB 
    represents the last element of the array.

    Similarly, “111” means we have taken all the 3 elements in our subset.

    So, if we have ‘n’ elements we need to have an integer that has its binary 
    representation ‘n’ bits long, which is (2^n)-1. So, every integer from 0 to (2^n)-1
    represents a different subset. 

    For checking, if an ith element is present in a subset or not we can say that if 
    the ith bit from LSB is set then the ith element is present in a subset otherwise 
    not.

*/

vector<int> subsetSum(vector<int> &nums) {
    vector<int> ans;
    int n = nums.size();

    // traverse to every subset from 0 to (2^N - 1)
    for (int i = 0; i < (1 << n); i++) { // (1 << n) means 2 ^ N

        int sum = 0; // take the sum for each subset

        for (int j = 0; j < n; j++) { 
            // traverse each subset and check is element is present in subset or not
            if ((1 << j) & i) {
                sum = sum + nums[i];
            }
        }

        ans.push_back(sum); // finally add the sum to ans
    }

    sort(ans.begin(), ans.end()); // sort the array for correct order

    return ans;
}