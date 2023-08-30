#include <iostream>
#include <vector>
using namespace std;

// In this question, we have given a knapsack of maximum weight and have some items
// with their weights and values in pair vector. Now we have to maximize the value 
// we can get with the help of this knapsack. It is different than general knapsack
// problem, if we have taken all element smaller than current maxWeight and still
// knapsack is not full, so we have to take accordingly remaining weight with its value
// from available large wight.

// Greedy Approach 
// Time Complexity: O(N * Log N)
// Space Complexity: O(1)

// make the sorting on the basis of fractional comparison
bool comparator(const pair<int, int> &p1, const pair<int, int> &p2) {
    double d1 = (1.0 * p1.second)/p1.first;
    double d2 = (1.0 * p2.second)/p2.first;

    return d1 > d2;
}

double maximumValue (vector<pair<int, int>>& items, int n, int maxWeight) {
    double ans = 0.0;
    int currWeight = 0;

    sort(items.begin(), items.end(), comparator);
    // sort the items according to fractional comparator

    for (int i=0; i<n; i++) {
        // if currWeight + curr item weight is less or equal than max weight, add it 
        // to ans

        if (currWeight + items[i].first <= maxWeight) {
            currWeight = currWeight + items[i].first;
            ans = ans + items[i].second;
        }
        else {
            // find the remaining weight
            int reqWeight = maxWeight - currWeight;
            ans = ans + ((1.0 * reqWeight/items[i].first) * items[i].second);
            // now, take that part of value which is required.
            // for example: if curr weight is 50 with value 40 & required weight is 30
            // for value, (30/50) * 40 = 24 will be required value for required weight
            // 30.

            break;
        }
    }

    return ans;
}