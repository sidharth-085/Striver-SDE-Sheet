#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// Approach 1: Brute Force Method
// Time Complexity: O(N * N)
// Space Complexity: O(1)

vector<int> prevGreaterElement(vector<int> &arr, int n) {
    vector<int> ans(n);
    // ans vector which stores the previous greater element for current element

    for (int i=0; i<n; i++) {
        int curr = arr[i];

        int leftIndex = i-1;
        // index for traversing one before for the current element

        // this loop will run until we found the element which is bigger than than 
        // current element

        while (leftIndex >= 0 && curr >= arr[leftIndex]) {
            leftIndex--;
        }
        
        // if we reached at the starting, it means all the elements before current 
        // element are smaller than current elements

        if (leftIndex == -1) {
            ans[i] = -1;
        }

        // if leftIndex != -1 means the value at leftIndex is the value which is
        // previou greater element for current element

        else {
            ans[i] = arr[leftIndex];
        }
    }

    return ans;
}

// Approach 2: Using Stack Method
// Time Complexity: O(N)
// Space Complexity: o(N)

vector<int> prevGreaterElement(vector<int> &arr, int n) {
    vector<int> ans(n);
    // ans vector to store the previous greater element for every element

    stack<int> stk;
    // stack using for keeping the track of previous elements

    for (int i=0; i<n; i++) {   
        // traverse the complete array in one go

        // run the loop until stack becomes empty or top element of stack is greater
        // than current element

        while (stk.empty() == false && arr[stk.top()] <= arr[i]) {
            stk.pop();
        }

        // and, if stack becomes empty, it means all the element before the current
        // elements are smaller than the current element

        if (stk.empty()) {
            ans[i] = -1;
        }

        // and if stack is non empty, top element of the stack is the previous greater
        // element for current element.

        else {
            ans[i] = arr[stk.top()];
        }

        stk.push(i);
        // add the current index into stack for complete traversal
    }

    return ans;
}

int main() {
    vector<int> arr;

    arr.push_back(5);
    arr.push_back(4);
    arr.push_back(3);
    arr.push_back(2);
    arr.push_back(1);
    arr.push_back(0);

    vector<int> ans = prevGreaterElement(arr, arr.size());

    for (int i=0; i<ans.size(); i++) {
        cout << ans[i] << " ";
    }
}