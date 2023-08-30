#include <iostream>
#include <vector>
using namespace std;

// Brute Force Approach: Time Complexity: O(2^N * N).
// 2^N subsets can be possible.

void helperSubsetSumToK(vector<int> &input, int size, int si, vector<int> output, int sum, vector<vector<int>> &ans) {
    if (sum==0 && output.size() != 0) {
        ans.push_back(output);
        return;
    }
    
    if (si==size) {
        return;
    }

    helperSubsetSumToK(input, size, si+1, output, sum, ans);
    
    output.push_back(input[si]);
    helperSubsetSumToK(input, size, si+1, output, sum-input[si], ans);
}

vector<vector<int>> findSubsetsThatSumToK(vector<int> arr, int size, int k) {
    vector<vector<int>> output;

    vector<int> currSubset;
    helperSubsetSumToK(arr, size, 0, currSubset, k, output);
    return output;
}

// Iterative & Bit Masking 

vector<vector<int>> findSubsetsThatSumToK(vector<int> &arr, int n, int k)
{
    // Ans vector contains all the subset which sum upto 'K'.
    vector<vector<int>> ans;

    for (int i = 0; i < (1 << n); i++)
    // 1 << n means 2 ^ n
    {
        int sum = 0;
        vector<int> vec;
        for (int j = 0; j < n; j++)
        {
            // Checking wheather the element is present the subset or not.
            if ((1 << j) & i)
            // 1 << j means current subset of 2 ^ j & i subset
            {
                sum += arr[j];
                vec.push_back(arr[j]);
            }
        }

        // If sum is 'K'.
        if (sum == k)
        {
            ans.push_back(vec);
        }
    }

    // Return ans.
    return ans;
}