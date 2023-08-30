#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

// Approach using Sorting
// Time Complexity: O(N * K * Log(N * K))

vector<int> mergeKSortedArrays(vector<vector<int>>&kArrays, int k) {
    vector<int> ans;
    for (int i=0; i<k; i++) {
        for (int j=0; j<kArrays[i].size(); j++) { // insert all elements one by one
            ans.push_back(kArrays[i][j]);
        }
    }

    sort(ans.begin(), ans.end());
    return ans;
}

// Approach using heap (Min Heap)
// Time Complexity: O(N * K * Log(K)).

vector<int> mergeKSortedArrays(vector<vector<int>>&kArrays, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i=0; i<k; i++) {
        for (int j=0; j<kArrays[i].size(); j++) { // insert all elements one by one
            pq.push(kArrays[i][j]);
        }
    }

    vector<int> ans;
    while (!pq.empty()) {
        int top = pq.top(); // take out from heap and insert in final array.
        pq.pop();

        ans.push_back(top);
    }
    return ans;
}

// Approach usng Divide and Conquer Algorithm (Merge Sort)
// Time Complexity: O(N * K * Log(K)).

vector<int> mergeTwoSortedArrays(vector<int> &arr1, vector<int> &arr2) {
    int size1 = arr1.size();
    int size2 = arr2.size();
    vector<int> ans;

    int i = 0; int j = 0;
    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) {
            ans.push_back(arr1[i]);
            i++;
        }
        else {
            ans.push_back(arr2[j]);
            j++;
        }
    }

    while (i < size1) {
        ans.push_back(arr1[i]);
        i++;
    } 
    while (j < size2) {
        ans.push_back(arr2[j]);
        j++;
    }

    return ans;
}

vector<int> mergeKSortedArraysHelper(vector<vector<int>> &kArrays, int start, int end) {
    if (start == end) {
        return kArrays[start];
        // if only one array is remaining, return that array.
    }

    if (start + 1 == end) {
        return mergeTwoSortedArrays(kArrays[start], kArrays[end]);
        // if only two arrays remaining, merge them and return 
    }

    int mid = start + (end - start)/2;

    vector<int> firstHalf = mergeKSortedArraysHelper(kArrays, start, mid);
    // sort the first half from start array to mid array.
    vector<int> secondHalf = mergeKSortedArraysHelper(kArrays, mid+1, end);
    // sort the second half from mid+1 array to end array.

    return mergeTwoSortedArrays(firstHalf, secondHalf);
    // finallly sort both arrays of firstHalf & secondHalf.
}

vector<int> mergeKSortedArrays(vector<vector<int>> &kArrays, int k) {
    int start = 0;
    int end = kArrays.size() - 1;
    return mergeKSortedArraysHelper(kArrays, start, end);
}