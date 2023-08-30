#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Approach 1: Brute Force Approach
// Time Complexity: O(N * K)
// Space Complexity: O(1)

int findFirstNegative(vector<int> &arr, int start, int end) {
    int firstNegative = 0;

    for (int i=start; i<=end; i++) {
        if (arr[i] < 0) {
            firstNegative = arr[i]; // when find the first negative value exit the loop.
            break;
        }
    }

    return firstNegative;
    // if all the values are positive from start to end, return 0 indicates no negative
    // element in current window.
}

vector<int> firstNegatives(vector<int> &arr, int k) {
    vector<int> ans;
    // anaswer vector stores all the values of first negatives for every window

    int n = arr.size();

    for (int i=0; i<n-k+1; i++) { // run the current loop for n-k+1 windows
        int firstNeg = findFirstNegative(arr, i, i+k-1);
        // first the first negative for current window from i to i+k-1.

        ans.push_back(firstNeg);
        // then push the value in ans vector
    }

    return ans;
}

// Approach 2: Sliding Window using Queue
// Time Complexity: O(N)
// Space Complexity: O(K)

vector<int> firstNegatives(vector<int> &arr, int k) {
    int n = arr.size();

    vector<int> ans;
    // anaswer vector stores all the values of first negatives for every window

    queue<int> q;
    // queue for maintaining the negative numbers in the queue order

    // push all the negative values of first window in the queue and front element of
    // queue indicates first negative element for current window

    for (int i=0; i<k; i++) {
        if (arr[i] < 0) {
            q.push(arr[i]); 
        }
    }

    // if q is empty, means for first window every element is positive, append 0 for
    // this case

    if (q.empty()) {
        ans.push_back(0);
    }

    // if q is non empty, add the front element to the answer which is first negative

    else {
        int first = q.front();
        ans.push_back(first);
    }

    int j = 0;
    // variable indicates starting of the previous window to be removed from current
    // window

    for (int i=k; i<n; i++) {
        // first check is q is non empty and front element of stack is same as element
        // to be removed for current window, if yes remove it from queue

        if (q.empty() == false && q.front() == arr[j]) {
            q.pop();
        }

        // check is current element is negative, add it to the queue

        if (arr[i] < 0) {
            q.push(arr[i]);
        }

        // now if q is empty, means all the elements are positive in current window
        // so append 0 to the answer

        if (q.empty()) {
            ans.push_back(0);
        }

        // if q is non empty, front element of queue is the first negative element for
        // current window

        else {
            int first = q.front();
            ans.push_back(first);
        }

        j++;
        // move the starting of the previous window ahead
    }   
    
    return ans;
}