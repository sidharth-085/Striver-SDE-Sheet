#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

// Brute Force Approach: Using Two Nested Loops

// Time Complexity: O(N^2)
// Space Complexity: O(1)

vector<vector<int>> pairSum(vector<int> &arr, int sum) {
	int size = arr.size();
	
	set<vector<int>> st; // we can store every pair into set
	vector<vector<int>> ans;

	sort(arr.begin(), arr.end());

	for (int i=0; i<size-1; i++) {
		for (int j=i+1; j<size; j++) {
			if (arr[i] + arr[j] == sum) {
				vector<int> temp = {arr[i], arr[j]};

				if (st.find(temp) == st.end()) { 
					// before adding to answer, check is it already present or not.
					ans.push_back(temp);
					st.insert(temp); // if not insert it for next use.
				}
			}
		}
	}
	return ans;
}

// Better Approach: Using Hashmaps
// Time Complexity: O(N^2)
// Space Complexity: O(N)

// This approach avoids duplicate pairs
vector<vector<int>> twoSum(vector<int>& arr, int sum) {
    vector<vector<int>> ans;
	unordered_map<int, int> freq;	

	for (int i=0; i<arr.size(); i++) {
		int complement = sum - arr[i];
		for (int j=0; j<freq[complement]; j++) {
            ans.push_back({min(arr[i], complement), max(arr[i], complement)});

			freq[arr[i]]--; // to avoid duplicate pairs, decrease their frequency 
			freq[complement]--; // both 42 & 43 line for getting duplicates
        }
		freq[arr[i]]++; // add the current to the map
	}
	// here we can sort it, if want in lexicographical order
	return ans;
}

// Optimal Approach using Two Pointer Approach
// Time Complexity: O(N)
// Space Complexity: O(1)

// This approach avoids duplicate pairs
vector<vector<int>> twoSum(vector<int>& arr, int target) {
    vector<vector<int>> ans;

	sort(arr.begin(), arr.end()); // sort to get correct answer
	int left = 0;
	int right = arr.size()-1;

	while (left < right) {
		int sum = arr[left] + arr[right];

		if (sum == target) {
			ans.push_back({arr[left], arr[right]});

			left++;
			right--;
		}
		else if (sum > target) {
			right--;
		}
		else {
			left++;
		}
	}

	return ans;
}