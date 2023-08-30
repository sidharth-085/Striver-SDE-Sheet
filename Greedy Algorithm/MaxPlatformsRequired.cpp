#include <iostream>
#include <algorithm>
using namespace std;

// We have two arrays of arrival time of trains and departure time of trains, we have to
// calculate the maximum number of platforms needed for these arrival and departure of 
// trains.

// Brute Force Approach: Store the number of platforms between arrival and departure time
// in another array.

// Time Complexity: O(2360 * N);
// Space Complexity: O(1)

int calculateMinPatforms(int arrival[], int departure[], int trains) {
    // keep an array of max 2360 size because for 24 hr, max time will be 2359

    int platforms[2360];
    for (int i=0; i<2360; i++) { // at starting, at everytime platform occupied is 0.
        platforms[i] = 0;
    }

    int numPlatforms = 1;

    // now traverse the given arrival & departure arrays

    for (int i=0; i<trains; i++) {
        // now for given arrival & departure time, incremenet the number of platforms 
        // required

        for (int j = arrival[i]; j <= departure[i]; j++) {
            platforms[j]++;

            // after incrementing platforms, update the numPlatforms to max platform 
            // required

            numPlatforms = max(numPlatforms, platforms[j]);
        }
    }

    return numPlatforms;
}

// Greedy Approach: Sort both arrival and departure times and traverse on different 
// times using Two - Pointer approach

// Time Complexity; O(N*LogN)
// Space Complexity: O(1)

int calculateMinPatforms(int arrival[], int departure[], int trains) {
    // keep starting from index 1 because first train always acquire platform.

    int currTrainTime = 1; 
    int prevTrainTime = 0;

    int numPlatforms = 1; // start from platfrom 1.
    int ans = 1; // the minimum platform the trains can occupy is 1.

    sort(arrival, arrival + trains);
    sort(departure, departure + trains);
    
    // sort the both arrival and departure arrays to get the proper arrival and departure
    // sequence of trains

    while (currTrainTime < trains && prevTrainTime < trains) {
        if (arrival[currTrainTime] <= departure[prevTrainTime]) { 
            // if the arrival time is less than or equal to departure time, the current 
            // train needs new platform to stand at it

            numPlatforms++;
            currTrainTime++; // move to next arrival time of train
        }
        else { 
            // if departure time is less, means train is departured and platform is 
            // vacant

            numPlatforms--;
            prevTrainTime++; // move to next departure time of train
        }

        ans = max(ans, numPlatforms); // maximize the platform number
    }

    return ans;
}

// Optimal Approach: Using Prefix sum of Platforms required

// Time Complexity: O(N)
// Space Complexity: O(1)

int calculateMinPatforms(int at[], int dt[], int n) {
    // Array to store the number of platforms required at different points of time.
    int platforms[2360] = {0};

    // Variable to store the final answer i.e. minimum number of platforms required.
    int minNumOfPlatforms = 1;

    for (int i = 0; i < n; i++) {

        // Increment the count of platforms at the time of arrival.
        platforms[at[i]]--;

        // Decrease the platform count just after the departure.
        platforms[dt[i] + 1]--;
    }

    // We are running loop till 2360 because maximum time value in a day can be 23:59.
    for (int i = 1; i < 2360; i++) {

        // Taking cumulative sum of platforms.
        platforms[i] = platforms[i] + platforms[i - 1];

        // Update minNumOfPlatforms.
        minNumOfPlatforms = max(minNumOfPlatforms, platforms[i]);
    }

    // Return the minimum number of platforms.
    return minNumOfPlatforms;
}