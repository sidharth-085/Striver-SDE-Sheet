#include <iostream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;

// Approach 1: Brute Force Method
// Time Complexity: O(N * N)
// Space Complexity: O(N)

vector<int> prevSmallerElement(vector<int> &arr, int n) {
    vector<int> ans(n);
    // answer vector to return at final

    for (int i=0; i<n; i++) {
        int curr = arr[i];
        int leftIndex = i-1;
        // make the index for traversal from one before the current element

        // run the loop until the element is smaller than current element
        while (leftIndex >= 0 && curr <= arr[leftIndex]) {
            leftIndex--;
        }

        // if leftIndex becomes -1 it means all the elements before current elements
        // are bigger than current element

        if (leftIndex == -1) {
            ans[i] = -1;
        }

        // if leftIndex is not -1, means the element at leftIndex is the previous
        // smaller element
        else {
            ans[i] = arr[leftIndex];
        }
    }

    return ans;
}

// Approach 2: Using the Stack Approach
// Time Complexity: O(N)
// Space Complexity: O(N)

vector<int> prevSmallerElement(vector<int> &arr, int n) {
    vector<int> ans(n);

    stack<int> stk;
    // make the stack checking the previous smaller elements

    for (int i=0; i<n; i++) {
        // run the loop until stack becomes empty or top element of stack becomes
        // smaller than current element

        while (stk.empty() == false && arr[stk.top()] >= arr[i]) {
            stk.pop();
        }

        // if stack becomes empty, means all the elements before the current element
        // are bigger than current element

        if (stk.empty()) {
            ans[i] = -1;
        }

        // if stack is non empty, top element of stack is the previous smaller element
        // for current element

        else {
            ans[i] = arr[stk.top()];
        }

        stk.push(i);
        // push the current index into stack for checking previous smaller
    }

    return ans;
}

int main() {
    vector<int> arr;

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);
    arr.push_back(6);

    vector<int> ans = prevSmallerElement(arr, arr.size());

    for (int i=0; i<ans.size(); i++) {
        cout << ans[i] << " ";
    }
}
