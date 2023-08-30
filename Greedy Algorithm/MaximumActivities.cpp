#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// same question as maximum meetings

// Approach 1: Greedy Algorithm
// Time Complexity: O(N * Log N)
// Space Complexity: O(N)

int maximumActivities(vector<int> &start, vector<int> &finish) {
    vector<pair<int, int>> activityTime;

    int n = start.size();
    for (int i = 0; i < n; i++) {
        activityTime.push_back({finish[i], start[i]}); 
        // map the finish time with start time
    }

    sort(activityTime.begin(), activityTime.end()); // sort according to end time 

    int maxAct = 1; // initially, activity is 1 for first activity
    int lastEnd = activityTime[0].first; // first activity completing time as curr End

    for (int i=0; i < n; i++) {
        if (activityTime[i].second >= lastEnd) { 
            // when start time of next activity is greater than equal to last end time
            // increase the activity number and mark current end time as last end time

            maxAct++;
            lastEnd = activityTime[i].first;
        }
    }

    return maxAct;
}