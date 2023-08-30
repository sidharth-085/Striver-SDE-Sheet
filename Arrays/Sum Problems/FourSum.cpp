#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

// Brute Force Approach: Using 4 nested loops
// Time Complexity: O(N^4)
// Space Complexity: O(1) {the ans vector not count in extra space}

vector<vector<int>> fourSum(vector<int> arr, int target, int n) {
    vector<vector<int>> ans;
    for (int i=0; i<n-3; i++) { 
        // we put n-3 instead of n, bcoz when there should be minimum 3 elements ahead 
        // i.e. j, k, l
        for (int j=i+1; j<n-2; j++) {
            // we put n-2 instead of n, bcoz when there should be minimum 2 elements 
            // ahead i.e. k, l
            for (int k=j+1; k<n-1; k++) {
            // we put n-1 instead of n, bcoz when there should be minimum 1 element 
            // ahead i.e. l
                for (int l=k+1; l<n; l++) {
                    long long sum = arr[i]; 
                    // this split addition is done to avoid sum exceed integer value
                    sum = sum + arr[j];
                    sum = sum + arr[k]; 
                    sum = sum + arr[l];

                    if (sum == target) {
                        vector<int> temp = {arr[i], arr[j], arr[k], arr[l]};
                        sort(temp.begin(), temp.end()); 
                        // sort to get all elements in sorted order
                        ans.push_back(temp);
                    }
                }
            }
        }
    }

    return ans;
}

// Better Brute Force Approach: Using Hashmap or Hashset for checking 4th element
// Time Complexity: O(N^3)
// Space Complexity: O(N) {the ans vector not count in extra space}

vector<vector<int>> fourSum(vector<int> arr, int target, int n) {
    vector<vector<int>> ans;
    for (int i=0; i<n-3; i++) {

        for (int j=i+1; j<n-2; j++) {

            unordered_map<int, int> map; // map to store 4th element.
            long long currSum = target - (arr[i] + arr[j]);

            for (int k=j+1; k<n; k++) {
                long long l = currSum - arr[k]; // check for 4th element
                if (map.find(l) != map.end()) { 
                    // if it is present in map, we found one quard
                    vector<int> temp = {arr[i], arr[j], arr[k], arr[l]};
                    sort(temp.begin(), temp.end()); // sort the elemets.
                    ans.push_back(temp);
                }
                map[arr[k]]++; // add the current 3rd element in map
            }
        }
    }

    return ans;
}

// Optimal Approach using Two Pointer Method: Keep two pointers for checking 4th element
// Time Complexity: O(N^3)
// Space Complexity: O(1) {the ans vector not count in extra space}

vector<vector<int>> fourSum(vector<int> &arr, int target, int n) {
    vector<vector<int>> ans;

    sort(arr.begin(), arr.end()); 
    // first sort the complete array to get correct order of quards.

    for (int i=0; i<n; i++) {
        if (i > 0 && arr[i] == arr[i-1]) { // if the prev and curr element is same, skip.
            continue;
        }

        for (int j=i+1; j<n; j++) { // if the prev and curr element is same, skip.
            if (j > i + 1 && arr[j] == arr[i-1]) {
                continue;
            }

            // two pointer approach
            int left = j+1; // keep two pointers (3rd element)
            int right = n-1; // 4th element

            while (left < right) {
                long long sum = arr[i]; // add all 4 elements i, j, left && right
                sum = sum + arr[j];
                sum = sum + arr[left];
                sum = sum + arr[right];

                if (sum == target) { // if sum is target, we found one quard
                    vector<int> temp = {arr[i], arr[j], arr[left], arr[right]};
                    ans.push_back(temp);

                    left++; // move both pointers.
                    right--;

                    while (left < right && arr[left] == arr[left-1]) {
                        left++; // if currently, prev and curr is same, skip it
                    }

                    while (left < right && arr[right] == arr[right+1]) {
                        right--; // if currently, prev and curr is same, skip it
                    }
                }
                else if (sum > target) { // if sum is more, move right back
                    right--;
                }
                else { // if sum is less, move right ahead.
                    left++;
                }
            }
        }
    }

    return ans;
}

// This approach only checks is there any four sum exists or not

/*
    Time Complexity: O(N^2)
    Space complexity: O(N^2)

    Where 'N' is the number of element present in the given array.
*/

bool commonIdx(pair < int, int > p1, pair < int, int > p2) {
    return p1.first == p2.first || p1.first == p2.second || p1.second == p2.first || p1.second == p2.second;
}

string fourSumAns(vector < int > arr, int target, int n) {
    unordered_map < int, pair < int, int >> mp;
    
    /* 
        Preparing a HashMap which will store sum of 
        two elements of array arr[] as key and their 
        indexes as value.
    */
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            mp[arr[i] + arr[j]] = {i, j};
        }
    }

    // Check on all possible pair sum which can be found in HashMap.
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int requiredSum = target - (arr[i] + arr[j]);
            /* 
                If HashMap contains required sum then we must 
                ensure that both pairs does not contain common indexes.
            */
            if (mp.find(requiredSum) != mp.end() && !commonIdx(mp[requiredSum], {i,j})) {
                return "Yes";
            }
        }
    }
    // If we can not found the target sum then we return No.
    return "No";
}