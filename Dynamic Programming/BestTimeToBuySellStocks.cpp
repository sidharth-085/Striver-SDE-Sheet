#include <iostream>
#include <vector>
using namespace std;

// Brute Force Approach
// Time Complexity: O(N^2)

int maximumProfit(vector<int> &arr){
    int size = arr.size();
    int diff = 0;

    for (int i=0; i<size-1; i++) {
        for (int j=i+1; j<size; j++) {
            if (arr[i] < arr[j] && diff < arr[j] - arr[i]) {
                diff = arr[j] - arr[i];
            }
        }
    }
    return diff;
}

// Optimal Approach 
// Time Complexity: O(N)

int maximumProfit(vector<int> &arr) {
    int maxProfit = 0, buy = arr[0];
    for (int i=1; i<arr.size(); i++) {
        int sell = arr[i];
        int currProfit = sell - buy;
        if (currProfit > maxProfit) {
            maxProfit = currProfit;
        }
        if (sell < buy) {
            buy = sell;
        }
    }
    return maxProfit;
}