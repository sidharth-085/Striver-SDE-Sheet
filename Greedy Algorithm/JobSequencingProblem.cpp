#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

// In job sequencing problem, we sort according to the particular factor (here max Profit)

// Approach 1: Greedy Approach

// Time Complexity: O(N*LogN + N*M)
// Space Complexity: O(M)
// where M is max Deadline

bool compare(const vector<int> &jobs1, const vector<int> &jobs2) { // compare function for sorting
    return jobs1[2] > jobs2[2];
}

vector<int> jobScheduling(vector<vector<int>> &jobs) {
    int n = jobs.size();

    // step 1: sort the complete jobs array according to maximum profit
    sort(jobs.begin(), jobs.end(), compare);

    // step 2: Find the maximum deadline from jobs to be done

    int maxDeadline = jobs[0][1];
    for (int i=1; i<n; i++) {
        maxDeadline = max(maxDeadline, jobs[i][1]);
    }

    // step 3: After finding maximum deadline, make a vector for keeping track of slots

    vector<int> slots(maxDeadline + 1, -1);
    // mark initially every slot as -1 to denote its empty

    // step 4: traverse the jobs array and fill slots array accordingly 

    int numJobs = 0;
    int maxProfit = 0;

    for (int i = 0; i < n; i++) { // loop for the job ids (o to n-1)
        for (int j = jobs[i][1]; j > 0; j--) { // loop for checking every slot is it empty or not
            if (slots[j] == -1) {
                slots[j] = i+1; // if the slot is empty put the current job id
                numJobs++; // increment the numJobs
                maxProfit = maxProfit + jobs[i][2]; // store the profit
                break; // if this slot is filled, check for next job id
            }
        }
    }

    // step 5: return numJobs && maxProfit
    
    return {numJobs, maxProfit};
}

// Approach using Sets: We can avoid the nested loop for finding the slot

// Time Complexity: O(N*LogN)
// Space Complexity: O(max deadline)

// Custom Comparator function to sort the jobs in the decreasing order of their profit.

vector<int> jobScheduling(vector<vector<int>> &jobs) {

    sort(jobs.begin(), jobs.end(), compare);

    int maxProfit = 0;
    int numberOfJobs = 0;
    int maxDeadline = 0;

    // Find the maximum deadline among all the jobs.
    for (int i = 0; i < jobs.size(); i++) {
        maxDeadline = max(maxDeadline, jobs[i][1]);
    }

    // Create a set "slots".
    set<int, greater<int>> slots;
    // here we are taking set which arranges element in decreasing order.
    // and, lower bound work becomes also opposite than normal.

    // Insert all the elements from maxDeadline to 1 into the set.
    for (int i = maxDeadline; i > 0; i--) {
        slots.insert(i);
    }
    vector<int> ans;

    for (int i = 0; i < jobs.size(); i++) {

        // If the set is empty or the deadline is less than the last element of the set, then ignore this job.
        if (slots.size() == 0 || jobs[i][1] < *slots.rbegin()) {
            // rbegin() function used for iteration from reverse
            continue;
        }

        int availableSlot = *slots.lower_bound(jobs[i][1]);
        // now this lower_bound return the just less than or equal iterator for jobs[i][1].

        maxProfit = maxProfit + jobs[i][2];
        numberOfJobs++;
        slots.erase(availableSlot);
    }

    ans.push_back(numberOfJobs);
    ans.push_back(maxProfit);
    return ans;
}