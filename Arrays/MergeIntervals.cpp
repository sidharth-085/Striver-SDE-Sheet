#include <iostream>
#include <vector>
using namespace std;

// We are given N number of intervals, we have to merge them if they are overlapping

/*
    intervals[i][0] = start point of i'th interval
    intervals[i][1] = finish point of i'th interval
*/

// Method 1: Brute Force
// Time Complexity: O(N * LogN + 2N) {2N due to 2 loops, not N^2}
// Space Complexity: O(N) {in worst case, no overlapping intervals}

vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
    int size = intervals.size();
    sort(intervals.begin(), intervals.end()); // sort the intervals to get overlapping

    vector<vector<int>> ans;
    int i = 0;

    while (i < intervals.size()) {
        int intervalMin = intervals[i][0]; // min of interval
        int intervalMax = intervals[i][1]; // max of interval

        int j;
        for (j = i + 1; j < intervals.size(); j++) { // start from one ahead till end
            if (intervalMax >= intervals[j][0]) { 
                // if intervalMax is larger than current minimum, means we found the 
                // overlapping intervals, update intervalMax with curr max
                intervalMax = max(intervalMax, intervals[j][1]);
            } 
            else { // and if there is no overlapping, push the final interval into vector
                break;
            }
        }

        ans.push_back({intervalMin, intervalMax});
        i = j; // Move to the next non-overlapping interval
    }

    return ans;
}

// Method 2: Optimal Approach
// Time Complexity: O(N*LogN + N)
// Space Complexity: O(N)

vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
    int size = intervals.size();

    sort(intervals.begin(), intervals.end());

    vector<vector<int>> ans;

    for (int i=0; i < size; i++) {
        int intervalMin = intervals[i][0];
        int intervalMax = intervals[i][1];
        
        if (ans.empty() || ans.back()[1] < intervals[i][0]) { 
            // if vector is empty or current interval in ans has maximum value less than 
            // current interval's minimum
            ans.push_back({intervalMin, intervalMax});
            continue;
        }

        if (ans.back()[1] >= intervals[i][0]) { 
            // if overlapping found update the interval in answer
            ans.back()[1] = max(ans.back()[1], intervals[i][1]);
        }
    }

    return ans;
}