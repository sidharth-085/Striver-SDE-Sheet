#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

// Approach Using Quick Select Algorithm
// Time Complexity: O(N*N)
// Space Complexity: O(N)

int partition(vector<int> &uniq, unordered_map<int, int> &mp, int left, int right, int pivot) {

    int pivotFrequency = mp[uniq[pivot]];

    int idx = left;

    // Move all less frequent elements to the left of the pivot.
    for (int i = left; i <= right; i++) {
        if (mp[uniq[i]] < pivotFrequency) {
            swap(uniq[idx], uniq[i]);
            idx++;
        }
    }

    // Move pivot to its final place.
    swap(uniq[idx], uniq[right]);

    return idx;
}

void quickselect(vector<int> &uniq, unordered_map<int, int> &mp, int left, int right, int kSmall) {
    // If the list contains only one element.
    if (left == right) {
        return;
    }

    // Find the position of pivot in the sorted list.
    int pivot = partition(uniq, mp, left, right, right);

    // If the pivot is in its final sorted position.
    if (kSmall == pivot) {
        return;
    }
    else if (kSmall < pivot) {
        // Move in the left direction.
        quickselect(uniq, mp, left, pivot - 1, kSmall);
    }
    else {
        // Move in the right direction.
        quickselect(uniq, mp, pivot + 1, right, kSmall);
    }
}

vector<int> KMostFrequent(int n, int k, vector<int> &arr) {
    vector<int> uniq;
    unordered_map<int, int> mp;

    // Build map where the key is element
    // and value is how often this element appears in 'ARR'.
    for (int ele : arr) {
        mp[ele]++;
    }

    int size = mp.size();
    uniq.assign(size, 0);

    int i = 0;

    // Build array of uniq elements.
    for (auto x : mp) {
        uniq[i] = x.first;
        i++;
    }

    // Perform quickselect.
    quickselect(uniq, mp, 0, size - 1, size - k);

    // Return top 'K' frequent elements
    vector<int> topK;
    for (int i = size - k; i < size; i++) {
        topK.push_back(uniq[i]);
    }

    return topK;
}

// Approach Using Heaps
// Time Complexity: O(N * LogN) {log N is due to inserting elements in heap, takes Log N time}
// Space Complexity: O(N) + O(N) {due to map && pq}

vector<int> KMostFrequent(int n, int k, vector<int> &arr) {
    unordered_map<int, int> map;
    for (int i=0; i<n; i++) {
        map[arr[i]]++;
    }

    priority_queue<pair<int,int>> pq;

    for (int i=0; i<n; i++) {
        if (map[arr[i]] != 0) {
            pq.push({map[arr[i]], arr[i]});
            map[arr[i]] = 0;
        }
    }

    vector<int> ans;
    for (int i=0; i<k; i++) {
        pair<int, int> top = pq.top();
        pq.pop();

        ans.push_back(top.second);
    }
    
    return ans;
}

// Approach 3: Bucket Sort: This algorithm has best case complexity O(N) when all the 
// elements are unique

// Time Complexity: O(N)
// Space Complexity: O(N)

vector<int> KMostFrequent(int n, int k, vector<int> &arr) {
    unordered_map<int, int> mp;

    // Build map where the key is element
    // and value is how often this element appears in 'ARR'.
    for (int ele : arr) {
        mp[ele]++; // use element as key
    }

    vector<vector<int>> bucket(n+1); 
    // this bucket will always have unique elements and we are pushing according to 
    // frequency (max can be n)

    for (auto x : mp) {
        int freq = x.second; // it holds the frequency of element

        // Add in correct bucket.
        bucket[freq].push_back(x.first); 
    }

    vector<int> ans;
    int cur = 0;

    // Add 'K' elements to answer array starting from the rightmost bucket.
    for (int i = n; i > 0 && k > 0; i--) {
        if (bucket[i].size() == 0) { // if there is bucket which is emapty, skip it
            continue;
        }

        for (int num : bucket[i]) { // traverse the current bucket and ad elements in ans
            ans.push_back(num);
            k--;
            if (k == 0) { // when k becomes zero, we have done with all k frequent elements
                break;
            }
        }
    }
    
    return ans;
}