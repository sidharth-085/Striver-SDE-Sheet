#include <vector>
using namespace std;

// This problem is similar to LIS (Longest Increasing Subsequence)

// DP approach

int maxIncreasingDumbbellsSum(vector<int> &rack, int n) {
	if (n == 1) {
		return rack[0];
	} 
	vector<int> maxSumIs(n); // array for storing the result

	for (int i=0; i<n; i++) {
		maxSumIs[i] = rack[i]; // initially every index have maximum increasing sum as its rack[i] 
	}

	for (int i=1; i<n; i++) {
		for (int j=i-1; j>=0; j--) {
			if (rack[i] > rack[j]) { // if we got the element which is lower than current
				int possibleAns = maxSumIs[j] + rack[i]; 
				maxSumIs[i] = max(maxSumIs[i], possibleAns);
                // check which one is maximum prev one or current one.
			}
		}
	}

	int maxAns = 0;
	
	for (int i=0; i<n; i++) {
		maxAns = max(maxAns, maxSumIs[i]); // now returns the maximum sum.
	}
	return maxAns;
}