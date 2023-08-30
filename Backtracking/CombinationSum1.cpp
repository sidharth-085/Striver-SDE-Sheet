#include <iostream>
#include <vector>
using namespace std;

// this is the famous problem of leetcode, in which we need to get the combinations of 
// elements to get the target sum. But we can include the number present in given array, 
// any number of times

void helper(vector<int> &arr, int target, int si, vector<int> &subArr, vector<vector<int>> &ans) {
    if (target == 0) {
        ans.push_back(subArr);
        return;
    }
    
    if (si == arr.size()) {
        return;
    }

    // first include the first element only if the curr element is less than target
    if (arr[si] <= target) {
        subArr.push_back(arr[si]); // add the element to the subarr and check for rem part

        helper(arr, target - arr[si], si, subArr, ans);
        // if we dont get desired answer and we returned back, we have to remove element.
        subArr.pop_back();  // backtrack and remove the element
    }
    helper(arr, target, si+1, subArr, ans);
}

vector<vector<int>> combSum(vector<int> &arr, int target) {
    sort(arr.begin(), arr.end());

    vector<int> subArr;
    vector<vector<int>> ans;

    helper(arr, target, 0, subArr, ans);
    return ans;
}