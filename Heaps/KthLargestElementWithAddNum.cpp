#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

// Approach 1: Using Priority Queue

// Time Complexity: O(Q*K)
// Space Complexity: O(N+Q)

// N is initial pool elements, Q are number of elements are added or num of queries and
// K is given k

class Kthlargest {
    priority_queue<int> pq;
    int k;

    int kthLargest(priority_queue<int> pq, int k) { 
        // function for calculating kth largest
        for (int i=0; i<k-1; i++) {
            pq.pop();
        }

        return pq.top();
    }
    
    public:

    Kthlargest(int k, vector<int> &arr) { 
        // constructor for inserting all elements in pq.
        int n = arr.size();
        this->k = k;
        for (int i=0; i<n; i++) {
            pq.push(arr[i]);
        }
    }

    int add(int num) { // add function to add the any element at any given time.
        pq.push(num);
        
        return kthLargest(pq, k);
    }

};