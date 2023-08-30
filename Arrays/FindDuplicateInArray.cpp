#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Approach 1: Brute Force
// Sort the elements & compare every two elements

int findDuplicate(vector<int> &arr, int n) { 
    // Sort the elements of the array.
    sort(arr.begin(), arr.end());
    // Traverse through the array to check if two consecutive elements are equal.
    for(int i = 0; i < n - 1; i++) {
        // Duplicate element found.
        if(arr[i] == arr[i+1]) {
            // Return the duplicate element.
            return arr[i];
        }
    }
    return -1;
}

// Approach 2: Binary Search

/*

	Time complexity: O(N * log(N)) 
	Space complexity: O(1)
	
	Where N is the length of the array.

*/

int findDuplicate(vector<int> &arr, int n) {
    // Initialise low and high pointers.
    int low = 1, high = n;

    // Find mid.
    while(low < high) {

        // Initialise mid element.
        int mid = low + (high - low) / 2;

        // Initialise count variable to count number of elements less than mid.
        int count = 0;

        // Count the number of elements smaller / equal to mid element.
        for(int i = 0; i < n; i++) {
            if(arr[i] <= mid) {
                count++;
            }
        }

        // Duplicate element is smaller than mid hence high = mid.
        if(count > mid) {
            high = mid;
        }

        // Duplicate element is larger than mid hence low = mid + 1.
        else { 
           low = mid + 1;
        }
    }
	
    return low;
}

// Using Heap: Time Complexity : O(N) & Space Complexity: O(N).

int findDuplicate(vector<int> &arr, int n) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i=0; i<n; i++) {
        pq.push(arr[i]);
    }
    
    int prevTop = -1;
    while (!pq.empty()) {
        int top = pq.top(); 
        pq.pop();
        if (prevTop == top) {
            return top;
        } 
        prevTop = top;
    }
    return -1;
}

// Using Hashmap

int findDuplicate(vector<int> &arr, int n) {
    unordered_map<int, int> map;
    for (int i=0; i<n; i++) {
        map[arr[i]]++;
        if (map[arr[i]] > 1) {
            return arr[i];
        }
    }
    return -1;
}

// Most Optimal Way is Floyd Tortoise-Hare Cycle Algorithm
// We have used this algorithm in Cycle Detection in LinkedList
// Time Complexity: O(N)
//  Space Complexity: O(1).

int findDuplicate(vector<int> &arr, int n) {
    int slow = arr[0];
    int fast = arr[0];
    // initially both pointers starting at 0th index.

    do {
        slow = arr[slow]; // slow moves one step ahead
        fast = arr[arr[fast]]; // fast moves two steps ahead.
    }  while (slow != fast); //  we will stop the loop when we we get both equal.

    // now when we find both slow == fast.
    // reset the slow to arr[0].

    slow = arr[0];
    while (slow != fast) {
        // now moves both pointers with same speed
        slow = arr[slow];
        fast = arr[fast];
    }

    // when slow and fast colloids again this is pointer where we find the duplicate.
    return slow;
}