#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Brute Force Appraoch: N*Logn due to sorting for every i number of elements till N
// so, Time Complexity is O(N^2 * Logn).

void findMedian(int *arr, int size) {
    vector<int> output;
    for (int i=0; i<size; i++) {
        output.push_back(arr[i]);
        sort(output.begin(), output.end());
        if (output.size() % 2 == 0) {
            int first = output[(output.size()/2)];
            int second = output[(output.size()/2) - 1];

            int avg = (first + second) / 2;
            cout << avg << " ";
        }
        else {
            cout << output[output.size()/2] << " ";
        }
    }
}

// Optimal Approach using Heaps
// Time Complexity: O(N)

void findMedian(int *arr, int size) {
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

    for (int i=0; i<size; i++) {
        // step 1: insert the element in appropriate heap
        if (maxHeap.empty() || maxHeap.top() > arr[i]) {
            maxHeap.push(arr[i]);
        }
        else {
            minHeap.push(arr[i]);
        }

        // step 2: check the size of both heaps and make it correct
        if (abs((int)maxHeap.size() - (int)minHeap.size()) > 1) {
            if (maxHeap.size() > minHeap.size()) {
                int temp = maxHeap.top();
                maxHeap.pop();
                minHeap.push(temp);
            }
            else {
                int temp = minHeap.top();
                minHeap.pop();
                maxHeap.push(temp);
            }
        }

        // step 3: check for the odd & even elements in heaps

        int median;
        if (maxHeap.size() == minHeap.size()) {
            median = (maxHeap.top() + minHeap.top())/2;
        }
        else if (maxHeap.size() > minHeap.size()) {
            median = maxHeap.top();
        }
        else {
            median = minHeap.top();
        }

        cout << median << " ";
    }
}