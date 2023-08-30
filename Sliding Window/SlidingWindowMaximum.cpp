#include <iostream>
#include <map>
#include <vector>
#include <deque>
using namespace std;

// Approach 1: Brute Force
// Time Complexity: O(N*N)
// Space Complexity: O(N)

int findMax(vector<int> &arr, int start, int end) {
    int maxAns = INT_MIN;

    for (int i=start; i<=end; i++) {
        maxAns = max(maxAns, arr[i]);
    }

    return maxAns;
}

vector<int> slidingWindowMaximum(vector<int> &arr, int &k) {
    vector<int> ans;
    int n = arr.size();

    // traverse all the n-k windows and find max for the every window
    for (int i=0; i<n-k+1; i++) {
        // find the maximum for current window from findMax function

        int maxAns = findMax(arr, i, i+k-1);

        ans.push_back(maxAns);
        // and add it to ans vector
    }

    return ans;
}

// Approach 2: Using Sliding Window with Map
// Time Complexity: O(N * Log K)
// Space Complexity: O(K)

vector<int> slidingWindowMaximum(vector<int> &arr, int &k) {
    vector<int> ans;

    int n = arr.size();
    
    // step 1: we are using map which stores greater element at the starting when
    // we add the elements to the map for every window

    map<int, int, greater<int>> maxMap;

    // step 2: for the first window, add all the elements in the map and at the begin()
    // we get the maximum element

    for (int i=0; i<k; i++) {
        maxMap[arr[i]]++;
    }

    // step 3: add the first element of map to the ans which is greatest

    int maxElement = maxMap.begin()->first;
    ans.push_back(maxElement);

    int j = 0;
    // variable stores the starting element of the previous window

    for (int i=k; i<n; i++) {
        // step 4: remove the previous window element from map and if frequency of that
        // element becomes 0, erase it from map

        maxMap[arr[j]]--;

        if (maxMap[arr[j]] == 0) {
            maxMap.erase(arr[j]);
        }

        // step 5: now just add the current element in the map and at the starting we
        // get the greatest element and we add it to the maxMap

        maxMap[arr[i]]++;

        int maxElement = maxMap.begin()->first;

        ans.push_back(maxElement);
        // finally add the maxElement to the ans and increment j for next window
        
        j++;
    }

    return ans;
}

// Approach 3: Using Sliding Window with Deque
// Time Complexity: O(N)
// Space Complexity: O(K)

vector<int> slidingWindowMaximum(vector<int> &arr, int &k) {
    int n = arr.size();

    vector<int> ans;
    
    // step 1: we are using deque here for keeping the track of larger to smaller 
    // elements in the dequeu for every k sized window

    deque<int> dq;

    // step 2: traverse the first window and push the elements in the deque.
    // if current element is bigger than already existing smallest element in deque
    // popback the last element of deque and insert the current element

    for (int i=0; i<k; i++) {
        while (dq.empty() == false && arr[i] >= arr[dq.back()]) {
            dq.pop_back();
        }

        dq.push_back(i);
    }

    // step 3: finally insert the front element which is greatest in the ans

    ans.push_back(arr[dq.front()]);

    int j = 0;
    // variable keeps track of starting element of previous window

    // variable keeps track of last element of current window
    for (int i=k; i<n; i++) { 
        // step 4: if the front index of deque belongs to the previous window, pop it
        // dont keep in the deque because we are keeping only current window elements

        while (dq.empty() == false && dq.front() <= j) {
            dq.pop_front();
        }

        // step 5: now just pops the element indices from back which are smaller than 
        // current element

        while (dq.empty() == false && arr[i] >= arr[dq.back()]) {
            dq.pop_back();
        }
        
        // step 6: now just push the current index in the deque for traversal

        dq.push_back(i);

        ans.push_back(dq.front());
        // also push the front element of the deque which is greatest in the current
        // window

        j++;
        // increments the j which is starting of the previous window
    }

    return ans;
}