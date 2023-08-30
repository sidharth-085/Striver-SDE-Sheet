#include <iostream>
#include <vector>
using namespace std;

// In this question, we have denominations {1, 2, 5, 10, 20, 50, 100, 500, 1000}
// and we have to find minimum coins to get a given sum value with these denominations

// Approach 1: Using Recursion (include and dont include pattern)
// Time Complexity: O(2^N)
// Space Complexity: O(N)

void minCoins(vector<int> &denominations, vector<int> &temp, int ei, int sum, vector<int> &ans) {
    if (sum == 0) {
        if (ans.size() > temp.size() || ans.size() == 0) {
            ans = temp;

            // we can use below code, deleting ans array and then copy temp to ans
            // ans.clear();
            // copy(temp.rbegin(), temp.rend(), back_inserter(ans));
        }
        return;
    }

    if (ei == -1) { // now reached to its 
        return;
    }

    if (denominations[ei] <= sum) { 
        // if current denomination is smaller or equal than sum.
        temp.push_back(denominations[ei]);

        // call for recursion for including the element
        minCoins(denominations, temp, ei, sum - denominations[ei], ans);    

        temp.pop_back(); // backtrack and remove the element from temp array
    }

    minCoins(denominations, temp, ei - 1, sum, ans); // find minCoins in temp
}

vector<int> minimumCoins(int sum) {
    vector<int> denominations = {1, 2, 5, 10, 20, 50, 100, 500, 1000} ;
    vector<int> ans; // finall answer vector
    vector<int> temp; // temporary vector for storing all the values and popping back.

    minCoins(denominations, temp, denominations.size() - 1, sum, ans);
    // now call the function and traverse in reverse, because we need order of
    // denominations in decreasing order so start with last i.e 1000

    return ans;
}

// Approach 2: Greedy Approach
// Time Complexity: O(N)
// Time Complexity: O(N)

vector<int> MinimumCoins(int sum) {
    vector<int> ans;
    int currSum = 0;
    
    int denominations[9] = {1, 2, 5, 10, 20, 50, 100, 500, 1000};

    for (int i = 8; i >= 0; i--) {
        while (currSum + denominations[i] <= sum) { // we are starting from big values
            currSum = currSum + denominations[i];
            ans.push_back(denominations[i]);
        }
    }

    return ans;
}