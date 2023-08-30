#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// This question is similar to Maximum Sum of Subarrays of Size k but little difference
// if there is window having non distinct elements, we dont consider this sum for
// maximum sum and move to next window

// Approach 1: Brute Force using Set
// Time Complexity: O(N * K)
// Space Complexity: O(K)

long long maximumSubarraySum(vector<int>& arr, int k) {
    int n = arr.size();

    long long maxSum = 0;

    for (int i=0; i<n-k+1; i++) { // traverse on every window i.e. till n-k+1.
        unordered_set<int> set;
        // make a set to count the distinct element for current window

        long long sum = 0;
        // sum for current window to be compare with maxSum.

        for (int j=i; j<i+k; j++) {
            set.insert(arr[j]); // insert every element for current window
            sum = sum + arr[j]; // add every element of current window to sum
        }

        // if set contains all distinct elements only then, consider the current sum
        // to compare with maxSum

        if (set.size() == k) {
            maxSum = max(maxSum, sum);
        }
    }

    return maxSum;
    // finally return the maxSum
}

// Approach 2: Sliding Window using Map
// Time Complexity: O(N)
// Space Complexity: O(K)

long long maximumSubarraySum(vector<int>& arr, int k) {
    int n = arr.size();

    long long maxSum = 0;
    // maxSum variable to store the maximum sum, initially it is 0.

    unordered_map<int, int> map;
    // we are keeping a map to check the distinct elements for every window

    long long sum = 0;
    // current sum for every window, initially it is 0.

    // for the first window, add all the elements in the map and take sum of all the 
    // elements

    for (int i=0; i<k; i++) {
        map[arr[i]]++;
        sum = sum + arr[i];
    }

    // if map size is k, i.e. all the elements in the map are distinct, only then we
    // will consider the sum for current window

    if (map.size() == k) {
        maxSum = max(maxSum, sum);
    }

    int j = 0;
    // pointer for the first element of the previous window to be removed now.

    for (int i=k; i<n; i++) {
        // first remove the previous window element and if the freqency becomes 0, 
        // erase it from map

        map[arr[j]]--;

        if (map[arr[j]] == 0) {
            map.erase(arr[j]);
        }

        // now also remove the previous window element from sum also

        sum = sum - arr[j];

        // then, include the current element in the map for current window elements

        map[arr[i]]++;

        // also add the current element to the sum

        sum = sum + arr[i];

        // if map size becomes k means all the elements for current window in map
        // are distinct, only now we should consider the sum

        if (map.size() == k) {
            maxSum = max(maxSum, sum);
        }
            
        j++;
        // now move the previous window starting element pointer to the right
    }

    return maxSum;
}