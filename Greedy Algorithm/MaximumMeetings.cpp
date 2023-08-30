#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Approach 1: Using Sorting Meeting end times and then traverse the start times
// Time Complexity: O(N * Log N)
// Space Complexity: O(N)

int maximumMeetings(vector<int> &start, vector<int> &end) {
    int n = start.size();

    vector<pair<int, int>> time; // make a array of pairs having end and start time.

    for (int i = 0; i < n; i++) {
        time.push_back({end[i], start[i]}); // add the end and start times in time.
    }

    sort(time.begin(), time.end()); // sort the time array according to end time

    int maxMeets = 1; // initially max meets is 1, because we surely attend first meeting
    int lastEnd = time[0].first; // make the first meeting end as last end till now

    for (int i = 1; i < n; i++) {
        if (time[i].second > lastEnd) { 
            // if current meeting's start time is more than last meeting's end time, 
            // we can take this meeting and make the last end as current meeting's end
            
            maxMeets++;
            lastEnd = time[i].first;
        }
    }

    return maxMeets; // finally return maxMeets
}