#include <iostream>
#include <vector>
using namespace std;

class MinHeap {
    vector<int> pq;
    
    public: 
    
    void insert(int element) {
        pq.push_back(element);

        int childIndex = pq.size() - 1;
        int parentIndex = (childIndex - 1)/2;
        
        while (childIndex > 0 && pq[parentIndex] > pq[childIndex]) {
            swap(pq[parentIndex], pq[childIndex]);
            
            childIndex = parentIndex;
            parentIndex = (childIndex - 1)/2;
        }
    }   
    
    int remove() {
        int ans = pq[0];
        pq[0] = pq[pq.size() - 1];
        pq.pop_back();
        
        int parentIndex = 0;
        int leftChildIndex = 2*parentIndex + 1;
        int rightChildIndex = 2*parentIndex + 2;
        while (leftChildIndex < pq.size()) {
            int minIndex = parentIndex;
            if (pq[minIndex] > pq[leftChildIndex]) {
                minIndex = leftChildIndex;
            }
            if (pq[minIndex] > pq[rightChildIndex]) {
                minIndex = rightChildIndex;
            }
            if (minIndex == parentIndex) {
                break;
            }
            
            swap(pq[minIndex], pq[parentIndex]);
            
            parentIndex = minIndex;
            leftChildIndex = 2*parentIndex + 1;
            rightChildIndex = 2*parentIndex + 2;
        }
        return ans;
    }    
};

// q queries represent two type of query
// 1. o x (here x represents the any number which is to be inserted in minheap).
// 2. 1 (It pops the minimum element from top and return that min value).

vector<int> minHeap(int n, vector<vector<int>>& q) {
    MinHeap mh;
    vector<int> ans;
    
    for (int i=0; i<n; i++) {
        if (q[i][0] == 0) {
            mh.insert(q[i][1]);
        }
        else if (q[i][0] == 1) {
            int temp = mh.remove();
            ans.push_back(temp);
        }
    }
    return ans;
}
