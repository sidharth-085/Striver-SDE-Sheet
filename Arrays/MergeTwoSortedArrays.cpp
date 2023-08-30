#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Brute force Solution
// Time Complexity: O(N*Logn)

vector<int> ninjaAndSortedArrays(vector<int>& arr1, vector<int>& arr2, int n, int m) {
    vector<int> ans;
    for (int i=0; i<n; i++) { // add elements of first array
        ans.push_back(arr1[i]);
    }
    for (int i=0; i<m; i++) { // add elements of second array
        ans.push_back(arr2[i]);
    }

    sort(ans.begin(), ans.end()); // sort the complete array
    return ans;
}

// Approach 2: Optimal One using Single loop
// Time Complexity: O(N)

vector<int> ninjaAndSortedArrays(vector<int>& arr1, vector<int>& arr2, int n, int m) {
	vector<int> ans;
	int i = 0;
	int j = 0;

	while (i < n && j < m) {
		if (arr1[i] <= arr2[j]) {
			ans.push_back(arr1[i]);
			i++;
		}
		else {
			ans.push_back(arr2[j]);
			j++;
		}
	}

	while (i < n) {
		ans.push_back(arr1[i]);
		i++;
	}
	
	while (j < m) {
		ans.push_back(arr2[j]);
		j++;
	}
	return ans;
}