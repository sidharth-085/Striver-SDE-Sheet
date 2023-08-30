#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

// Brute Force Method
// Time Complexity: O(N^3)
// Space Complexity: O(1)

vector<vector<int>> findTriplets(vector<int> &arr, int n, int target) {
	set<vector<int>> st; // set to avoid duplicate triplets
	vector<vector<int>> ans;

	sort(arr.begin(), arr.end()); // first sort the array to get correct answer

	for (int i=0; i<n-2; i++) { // loop 1 
		for (int j=i+1; j<n-1; j++) { // loop 2 
			for (int k=j+1; k<n; k++) { // loop 3
				int sum = arr[i] + arr[j] + arr[k];

				if (sum == target) {
					vector<int> temp = {arr[i], arr[j], arr[k]};
					if (st.find(temp) == st.end()) { 
						// if it is not present in set, add it to ans && set
						ans.push_back(temp);
						st.insert(temp);
					}
				}
			}
		}
	}

	return ans;
}

// Better Approach using Hashmap

vector<vector<int>> findTriplets(vector<int> &arr, int n, int target) {
	
}

// Two Pointer Approach
// Time Complexity: O(N^2 + N*LogN)
// Space Complexity: O(1)

vector<vector<int>> findTriplets(vector<int> &arr, int n, int target) {
	// Step 1: Sort the complete array
	sort(arr.begin(), arr.end());

	vector<vector<int>> ans;

	for (int i=0; i<n-1; i++) { // loop for fixing the first elements
		if (i > 0 && arr[i] == arr[i-1]) { // skip duplicates
			continue;
		}

		int left = i+1; // two pointer approach 
		int right = n-1;

		while (left < right) {
			int sum = arr[i] + arr[left] + arr[right];

			if (sum == target) {
				vector<int> temp = {arr[i], arr[left], arr[right]};
				ans.push_back(temp);

				left++;
				right--;
				
				// skip the duplicate ones in the left
				while (left < right && arr[left] == arr[left-1]) {
					left++;
				}
				
				// skip the duplicate ones in the right
				while (left < right && arr[right] == arr[right+1]) {
					right--;
				}
			}
			else if (sum > target) {
				right--;
			}
			else {
				left++;
			}
		}
	}

	return ans;
}