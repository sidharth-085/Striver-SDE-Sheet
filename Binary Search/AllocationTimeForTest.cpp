#include <iostream>
#include <vector>
using namespace std;

// Problem is same as Book Allocation

// Approach 1: Linear Search
// Time Complexity: O((totalTime - maxTime + 1)*N)
// Space Complexity: O(1)

long long countDays(vector<int> &time, int chapters, long long i) {
    long long requiredDays = 1;
    
    long long currDays = 0;

    for (int j=0; j<chapters; j++) {
        if (currDays + time[j] <= i) {
            currDays = currDays + time[j];
        }
        else {
            requiredDays++;
            currDays = time[j];
        }
    }

    return requiredDays;
}

long long ayushGivesNinjatest(int days, int chapters, vector<int> time) {	
    if (days > chapters) {
        return -1;
    }

    long long maxTime = (long long)(time[0]);
    long long totalTime = 0;
    
    for (int i=0; i<chapters; i++) {
        maxTime = max(maxTime, (long long)(time[i]));
        totalTime = totalTime + time[i];
    }

    long long low = maxTime;
    long long high = totalTime;

    for (long long i = maxTime; i<=totalTime; i++) {
        long long requiredDays = countDays(time, chapters, i);

        if (requiredDays > days) {
            continue;
        }
        else {
            return i;
        }
    }

    return -1;
}

// Approach 2: Binary Search
// Time Complexity: O(Log(totalTime - maxTime + 1) * N)
// Space Complexity: O(1)

long long countDays(vector<int> &time, int chapters, long long i) {
    long long requiredDays = 1;
    
    long long currDays = 0;

    for (int j=0; j<chapters; j++) {
        if (currDays + time[j] <= i) {
            currDays = currDays + time[j];
        }
        else {
            requiredDays++;
            currDays = time[j];
        }
    }

    return requiredDays;
}

long long ayushGivesNinjatest(int days, int chapters, vector<int> time) {	
    if (days > chapters) {
        return -1;
    }

    long long maxTime = (long long)(time[0]);
    long long totalTime = 0;
    
    for (int i=0; i<chapters; i++) {
        maxTime = max(maxTime, (long long)(time[i]));
        totalTime = totalTime + time[i];
    }

    long long low = maxTime;
    long long high = totalTime;

    while (low <= high) {
        long long mid = low + (high - low)/2;

        long long requiredDays = countDays(time, chapters, mid);

        if (requiredDays > days) {
            low = mid+1;
        }
        else {
            high = mid-1;
        }
    }
    
    return low;
}