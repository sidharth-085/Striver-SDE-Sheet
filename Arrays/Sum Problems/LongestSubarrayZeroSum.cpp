#include <iostream>
using namespace std;

// Brute Force Approach
// Time Complexity: O(N*N)
// Space Complexity: O(1)

int LongestSubsetWithZeroSum(vector <int> arr) {
    int maxLength = 0;
    for (int i=0; i<arr.size(); i++) {
        int sum = 0;

        for (int j=i; j<arr.size(); j++) {
            sum = sum + arr[j];

            if (sum == 0) {
                maxLength = max(maxLength, j - i + 1);
            }
        }
    }

    return maxLength;
}

// Optimal Approach using Hashmap
// Time Complexity: O(N)
// Space Complexity: O(N).

int LongestSubsetWithZeroSum(vector <int> arr) {
    unordered_map<int, int> map; // stores corresponding prefix sum at particular ith index
    int size = arr.size();

    int maxLenAns = 0;
    int prefixSum = 0;

    for (int i=0; i<size; i++) {
        // step 1: calculate the current prefix sum till i

        prefixSum = prefixSum + arr[i];

        // step 2: check is current prefix sum is 0, make maxLenAns = i + 1.

        if (prefixSum == 0) {
            maxLenAns = i + 1;
        }

        // step 3: check is maxLenAns already exists in map, if yes then it means 
        // between the current index and previous same sum index has subarray having
        // sum 0.

        if (map.find(prefixSum) != map.end()) { // if sum already there, update length of max
            maxLenAns = max(maxLenAns, i - map[prefixSum]);
        }
        else {
            map[prefixSum] = i; // else add that sum with index in map.
        }
    }

    return maxLenAns;
}