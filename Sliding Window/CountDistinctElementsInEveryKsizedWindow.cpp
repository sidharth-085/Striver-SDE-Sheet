#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

// Approach 1: Extreme Brute Force
// Time Complexity: O(N * K * K)
// Time Complexity: O(1)

vector<int> countDistinctElements(vector<int> &arr, int k) {
    int n = arr.size();

    vector<int> result;

    // loop for traversing n - k windows for given k size window
    for (int i=0; i<n-k+1; i++) {
        int count = 0;
        // maintains count for counting unique elements in every window
        
        // start from i and go till (i + k - 1) => size of window
        for (int j=i; j<i+k; j++) {
            bool distinct = true;
            // flag for looking is current element is distinct or not

            // check for every element, is current element arr[j] is distinct or not
            for (int z=j+1; z<i+k; z++) {
                if (arr[j] == arr[z]) { // if found the same break the loop
                    distinct = false;
                    break;
                }
            }

            if (distinct == true) { // only increments count when distinct is true
                count++;
            }
        }

        result.push_back(count); // finally add the count for ith window in result
    }

    return result;
}

// Approach 2: Brute Force using Hashmap
// Time Complexity: O((N-K) * K)
// Space Complexity: O(N)

vector<int> countDistinctElements(vector<int> &arr, int k) {
    vector<int> ans;
    int n = arr.size();

    for (int i=0; i<n-k+1; i++) {
        unordered_set<int> set;
        // using set for avoiding duplicate elements

        for (int j=i; j<i+k; j++) {
            set.insert(arr[j]);
            // push every element in set for current window
        }

        ans.push_back(set.size());
        // insert the size of current size which is number of distinct elements in
        // ans vector
    }

    return ans;
}

// Approach 3: Using Sliding Window
// Time Complexity: O(N)
// Space Complexity: O(N)

vector<int> countDistinctElements(vector<int> &arr, int k) {
    int n = arr.size();

    unordered_map<int, int> map;
    // here we are using map for sliding window which maintains count for each element
    // in the given window

    // for the first window, insert all the elements in map

    for (int i=0; i<k; i++) {
        map[arr[i]]++;
    }

    vector<int> result;
    result.push_back(map.size());
    // add the size of map which is distinct elements for 1st window

    int j = 0;
    // variable to maintain the starting of previous window

    // start the loop from k which represents the last pointer of next window
    for (int i=k; i<n; i++) {
        map[arr[j]]--;
        // first remove the starting element of previous window from map

        if (map[arr[j]] == 0) { // if the frequency becomes 0, erase it from map
            map.erase(arr[j]);
        }

        map[arr[i]]++;
        // then finally add the last element of next window to map

        result.push_back(map.size()); 
        // then, add the size of map which counts the number of distinct elements in the current window
        
        j++;
        // finally increments j which represents starting element of previous window
    }

    return result;
}